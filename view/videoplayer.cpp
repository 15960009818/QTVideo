#include "videoplayer.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStyle>
#include <QDebug>
#include <QMediaPlayer>
#include <QBuffer>
#include <QResource>
VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent)
{
// 设置布局
   QVBoxLayout *layout = new QVBoxLayout(this);

   // 创建视频小部件
   videoWidget = new QVideoWidget();
   videoWidget->setMinimumSize(640, 480);
   // 创建媒体播放器
   player = new QMediaPlayer();
   player->setVideoOutput(videoWidget);

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

   // 连接播放器的信号到槽函数
   connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
   connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);

   connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), [=](QMediaPlayer::Error error) {
       qDebug() << "Media error:" << player->errorString();
   });
   connect(player, &QMediaPlayer::stateChanged, [](QMediaPlayer::State state) {
       qDebug() << "MediaPlayer state changed:" << state;
   });

   // 添加部件到布局
   layout->addWidget(videoWidget);
   layout->addWidget(slider);
   layout->addWidget(playButton);
   layout->addWidget(pauseButton);
   layout->addWidget(stopButton);

   // 创建打开文件按钮
   QPushButton *openButton = new QPushButton("Open");
   connect(openButton, &QPushButton::clicked, this, &VideoPlayer::openFile);
   layout->addWidget(openButton);

}

void VideoPlayer::playVideo(const QString &videoPath) {

    QDir dir(QDir::currentPath()); // 获取当前工作目录
    dir.cdUp(); // 移动到上一级目录
    QString absolutePath = dir.filePath(videoPath);
    player->setMedia(QUrl::fromLocalFile(absolutePath)  );
    player->play();
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
