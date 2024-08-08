#ifndef VIDEO_H
#define VIDEO_H
#include <QString>

class Video
{
private:
    int videoId;
    QString videoName;
    QString videoCover;
    QString videoPath;
public:
    Video();
    Video(int videoId,    QString videoName,    QString videoCover,    QString videoPath);
    int getVideoId() const;
    void setVideoId(int value);
    QString getVideoName() const;
    void setVideoName(const QString &value);
    QString getVideoCover() const;
    void setVideoCover(const QString &value);
    QString getVideoPath() const;
    void setVideoPath(const QString &value);
};

#endif // VIDEO_H
