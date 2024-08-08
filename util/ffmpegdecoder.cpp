#include "ffmpegdecoder.h"
#include <QDebug>
#include <QImage>
#include <QDir>
#include <QPainter>
#include <QVBoxLayout>
#include <QRegularExpression>
FFmpegDecoder::FFmpegDecoder(QWidget  *parent)
    : QWidget(parent)
{
    initializeFFmpeg();
    this->timer= new QTimer();
    this->video = new QLabel(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(video);
    setLayout(layout);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

FFmpegDecoder::~FFmpegDecoder()
{
    cleanup();
}
void FFmpegDecoder::initializeFFmpeg()
{
    av_register_all();
}

void FFmpegDecoder::cleanup()
{
    if (swsCtx) {
       sws_freeContext(swsCtx);
       swsCtx = nullptr;
   }
   if (buffer) {
       av_free(buffer);
       buffer = nullptr;
   }
   if (rgbPicture) {
       av_frame_free(&rgbPicture);
       rgbPicture = nullptr;
   }
   if (picture) {
       av_frame_free(&picture);
       picture = nullptr;
   }
   if (pcodecCtx) {
       avcodec_close(pcodecCtx);
       pcodecCtx = nullptr;
   }
   if (pFormatCtx) {
       avformat_close_input(&pFormatCtx);
       pFormatCtx = nullptr;
   }
}

void FFmpegDecoder::setupTimer(int fps)
{

    timer->start(1000/fps); // 根据 FPS 设置定时器间隔
}


void FFmpegDecoder::onTimeout()
{
    //qDebug()<<"onTimeout";

    //qDebug()<<currentFrameIndex;
    if (currentFrameIndex >= imageFiles.size()) {
        timer->stop();
        return;
    }

    QString imgPath = "img_output/" + imageFiles[currentFrameIndex];
    currentImage.load(imgPath);
    // 调整 QPixmap 的大小以适应 videoWidget
    QPixmap pixmap = QPixmap::fromImage(currentImage);
    video->setPixmap(pixmap.scaled(video->size(), Qt::KeepAspectRatio));
    currentFrameIndex++;
}


bool FFmpegDecoder::decodeVideo()
{
    FILE *fp = fopen("video/temp.h264","wb");

    pkt= (AVPacket*)malloc(sizeof(AVPacket));
    QString path ="img_output/";
    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    foreach(QFileInfo file, dir.entryInfoList()) {
        QFile::remove(file.absoluteFilePath());
    }
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    foreach(QFileInfo subDir, dir.entryInfoList()) {
        QDir(subDir.absoluteFilePath()).removeRecursively();
    }
    qDebug()<< "decoding .....";
    int count = 0;
    char imgPath[256] = {0};
    while(av_read_frame(pFormatCtx,pkt) == 0)
    {
        if(pkt->stream_index == videoIndex) //判断本帧是否是视频数据的码流
        {
            fwrite(pkt->data,pkt->size,1,fp); // 将一帧的码流数据写入文件
            //让每帧画面转换原始像素图片，在qt窗口中展示
            int got_picture_ptr= -1; //操作状态信息，如果不为0表示解码成功/
            //从一帧的视频码流信息中解析出图像信息
            avcodec_decode_video2(pcodecCtx,picture,&got_picture_ptr,pkt);
            if(got_picture_ptr != 0 )//解码成功
            {
                //剔除图像中的无效信息，生成最终的原始图像
                //1。剔除规则，剔除前的图像数据，剔除前图像的大小，剔除前图像的高度
                //剔除后图像数据，剔除后图像大小,剔除后图像高度
                sws_scale(swsCtx,picture->data,picture->linesize,0
                          ,picture->height,rgbPicture->data,rgbPicture->linesize);
                count++;
                //if(count % 25 != 0) continue;
                //将图片转存到QImage中，
                QImage img = QImage((uchar *)buffer, pcodecCtx->width,pcodecCtx->height,
                                    QImage::Format_RGB32);
                sprintf(imgPath,"img_output/img%d.jpg",count);
                //保存成图片文件
                img.save(imgPath);

            }
        }
        av_packet_unref(pkt); // 清除已经使用的包
    }
    imageFiles =  dir.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    QRegularExpression rx("\\d+");

       // 使用lambda函数提取数字并进行排序
       std::sort(imageFiles.begin(), imageFiles.end(), [&rx](const QString &a, const QString &b) {
           QRegularExpressionMatch matchA = rx.match(a);
           QRegularExpressionMatch matchB = rx.match(b);

           int numA = matchA.hasMatch() ? matchA.capturedTexts().first().toInt() : 0;
           int numB = matchB.hasMatch() ? matchB.capturedTexts().first().toInt() : 0;

           return numA < numB;
       });
    fclose(fp);
    qDebug()<< "decoder is finish...";
}

bool FFmpegDecoder::openVideo(const QString &filePath)
{
    //2.打开视频文件，获得解码或编码的多媒体格式的上下文
    pFormatCtx= avformat_alloc_context();//准备保存视频信息的核心对象
    int res=avformat_open_input(&pFormatCtx,filePath.toUtf8().data(),nullptr,nullptr);
    if(res !=0)
    {
        qDebug()<<"avformat_open_input is error";
        return false ;
    }
    qDebug()<<"avformat_open_input is success";
    //3.从avformatContext解析出流媒体信息
    res = avformat_find_stream_info(pFormatCtx,nullptr);
    if(res != 0)
    {
        qDebug()<<"avformat_find_stream_info is error";
        return false;
    }
    qDebug()<<"avformat_find_stream_info is success";
    //4.从流信息中取出查找视频流

    for(int i=0;i<pFormatCtx->nb_streams;++i)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            videoIndex = i;
            break;
        }
    }
    if(videoIndex == -1)
    {
        qDebug() <<"video stream is not found";
        return false ;
    }
    qDebug() << "video stream index is " << videoIndex;
    //  5.获取合适的编解码器
    pcodecCtx = pFormatCtx->streams[videoIndex]->codec;
    AVCodec *decoder = avcodec_find_decoder(pcodecCtx->codec_id);
    if(decoder == nullptr)
    {
        qDebug()<<"avcodec_find_decoder is error";
        return false;
    }
    qDebug()<<"avcodec_find_decoder is success";\
    //6.打开解码器
    res = avcodec_open2(pcodecCtx,decoder,nullptr);
    if(res != 0)
    {
        qDebug()<<"avcodec_open2 is error";
        return false;
    }
    qDebug()<<"avcodec_open2 is success";
    //7.解码 （从视频码流中提取一帧帧的原始像素信息）

    //初始化avframe(1、压缩后的图像码流，2.解压后的图像（去除无用像素信息），3.)
    picture = av_frame_alloc();// 用于保存解压前的图像信息
    rgbPicture = av_frame_alloc();//用于保存解压后的原始图像信息
    //从上下文容器中读取一帧的视频流数据，保存到AVPacket中
    picture->width = pcodecCtx->width;
    picture->height = pcodecCtx->height;
    picture->format = pcodecCtx->pix_fmt;

    rgbPicture->width = pcodecCtx->width;
    rgbPicture->height = pcodecCtx->height;
    rgbPicture->format = pcodecCtx->pix_fmt;

    int numbyte = avpicture_get_size(AV_PIX_FMT_RGB32,picture->width,picture->height);
    //设置过滤规则（转置）
    buffer = (uint8_t *)av_malloc(numbyte * sizeof (uint8_t));
    //图片初始化填充，用于保存最终生成的图片
    avpicture_fill((AVPicture*)rgbPicture,buffer,AV_PIX_FMT_RGB32,
                   pcodecCtx->width,pcodecCtx->height);
    swsCtx = sws_getContext(pcodecCtx->width,pcodecCtx->height,pcodecCtx->pix_fmt,
                                        pcodecCtx->width,pcodecCtx->height,AV_PIX_FMT_RGB32,
                                        SWS_BICUBIC,nullptr,nullptr,nullptr);
    // 获取 FPS 并设置定时器
    AVRational frameRate = pFormatCtx->streams[videoIndex]->avg_frame_rate;
    int fps = frameRate.num / frameRate.den;
    qDebug() << "FPS:" << fps;
    this->setupTimer(fps);
    return true;
}

