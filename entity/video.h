#ifndef VIDEO_H
#define VIDEO_H
#include <QString>

class Video
{
public:
    int getVideoId() const { return videoId; }
    void setVideoId(int id) { videoId = id; }

    QString getVideoName() const { return videoName; }
    void setVideoName(const QString &name) { videoName = name; }

    QString getVideoImage() const { return videoImage; }
    void setVideoImage(const QString &image) { videoImage = image; }

    QString getVideoPath() const { return videoPath; }
    void setVideoPath(const QString &path) { videoPath = path; }

private:
    int videoId;
    QString videoName;
    QString videoImage;
    QString videoPath;
};


#endif // VIDEO_H
