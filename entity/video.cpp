#include "entity/video.h"



int Video::getVideoId() const
{
    return videoId;
}

void Video::setVideoId(int value)
{
    videoId = value;
}

QString Video::getVideoName() const
{
    return videoName;
}

void Video::setVideoName(const QString &value)
{
    videoName = value;
}

QString Video::getVideoCover() const
{
    return videoCover;
}

void Video::setVideoCover(const QString &value)
{
    videoCover = value;
}

QString Video::getVideoPath() const
{
    return videoPath;
}

void Video::setVideoPath(const QString &value)
{
    videoPath = value;
}

Video::Video()
{

}

Video::Video(int videoId, QString videoName, QString videoCover, QString videoPath)
{
    this->videoId=videoId;
    this->videoName=videoName;
    this->videoCover=videoCover;
    this->videoPath=videoPath;
}
