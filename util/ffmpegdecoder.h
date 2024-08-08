#ifndef FFMPEEG_H
#define FFMPEEG_H
// extern "C"是为了实现类C和C++的混合编程
// 因为ffmpeg是用C写的，故而在C++引入ffmpeg的C函数库需加此声明
extern "C"
{
    #include "libavcodec/avcodec.h"     //编解码库
    #include "libavdevice/avdevice.h"   //输入输出设备库；读取摄像头的
    #include "libavfilter/avfilter.h"   //音视频滤镜库；进行音视频处理与编辑
    #include "libavformat/avformat.h"   //文件格式和协议库
    #include "libavutil/avutil.h"       //音视频处理
    #include "libswresample/swresample.h"   //音频重采样
    #include "libswscale/swscale.h"     //图像进行格式转换
}

#include <QString>
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QPaintEvent>
#include <QLabel>
class FFmpegDecoder : public QWidget
{
    Q_OBJECT

public:

    FFmpegDecoder(QWidget  *parent = nullptr);
    ~FFmpegDecoder();
    bool openVideo(const QString &filePath);
    bool decodeVideo();
signals:
    void frameDecoded(const QImage &image);

private slots:
    void onTimeout();

private:
    AVFormatContext *pFormatCtx = nullptr;
    AVCodecContext *pcodecCtx = nullptr;
    AVFrame *picture = nullptr;
    AVFrame *rgbPicture = nullptr;
    SwsContext *swsCtx = nullptr;
    int videoIndex = -1;
    uint8_t *buffer = nullptr;
    QTimer *timer = nullptr;
    QImage currentImage;
    AVPacket *pkt =nullptr;
    QStringList imageFiles;
    int currentFrameIndex = 0;
    QLabel *video;
    void initializeFFmpeg();
    void cleanup();
    void setupTimer(int fps);
};

#endif // FFMPEEG_H
