#include "videoplayer.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStyle>
#include <QDebug>
#include <QMediaPlayer>
#include <QBuffer>
#include <QResource>
#include <QLabel>
#include "view/ffmpegdecoder.h"
#include <entity/video.h>
VideoPlayer::VideoPlayer(Video video,QWidget *parent) : QWidget(parent)
{
    // 设置主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    this->video =video;
    // 创建视频小部件
    videoWidget = new QVideoWidget();
    videoWidget->setMinimumSize(640, 480);

    // 创建媒体播放器
    player = new QMediaPlayer();
    player->setVideoOutput(videoWidget);

    // 创建左侧布局（视频播放区域）
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(videoWidget);

    // 创建右侧布局（视频信息）
    QVBoxLayout *rightLayout = new QVBoxLayout();

    // 创建视频信息显示部件
    QLabel *infoLabel = new QLabel(video.getVideoName());
    rightLayout->addWidget(infoLabel);

    // 添加左侧和右侧布局到主布局
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    // 创建播放按钮
    QPushButton *playButton = new QPushButton();
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QPushButton::clicked, this, &VideoPlayer::togglePlayback);

    // 创建暂停按钮
    QPushButton *pauseButton = new QPushButton();
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);

    // 创建停止按钮
    QPushButton *stopButton = new QPushButton();
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);

    // 创建进度条
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 0);
    connect(slider, &QSlider::sliderMoved, this, &VideoPlayer::seek);

    // 创建底部布局
    QVBoxLayout *bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(playButton);
    bottomLayout->addWidget(pauseButton);
    bottomLayout->addWidget(stopButton);
    bottomLayout->addWidget(slider);

    // 将底部布局添加到左侧布局的底部
    leftLayout->addLayout(bottomLayout);

    // 创建打开文件按钮
    QPushButton *openButton = new QPushButton("Open");
    connect(openButton, &QPushButton::clicked, this, &VideoPlayer::openFile);
    rightLayout->addWidget(openButton);

    // 连接播放器的信号到槽函数
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);

    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), [=](QMediaPlayer::Error error) {
        qDebug() << "Media error:" << player->errorString();
    });
    connect(player, &QMediaPlayer::stateChanged, [](QMediaPlayer::State state) {
        qDebug() << "MediaPlayer state changed:" << state;
    });
}

void VideoPlayer::playVideo(const QString &videoPath) {

    FFmpegDecoder *decoder = new FFmpegDecoder(videoWidget);

    decoder->resize(videoWidget->width(), videoWidget->height());


    if (decoder->openVideo(videoPath)) {
         decoder->decodeVideo();
         decoder->show();
    }
}

void VideoPlayer::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Video File", "", "Video Files (*.mp4 *.avi *.mkv)");
    qDebug()<<fileName;
    if (!fileName.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->play();
    }
}

void VideoPlayer::togglePlayback() {
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void VideoPlayer::seek(int position) {
    player->setPosition(position);
}
