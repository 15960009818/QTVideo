#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QSlider>

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    void playVideo(const QString &videoPath);
private slots:
    void openFile();
    void togglePlayback();
    void seek(int position);
private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QSlider *slider;
};

#endif // VIDEOPLAYER_H
