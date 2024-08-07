#ifndef VIDEOSERVICE_H
#define VIDEOSERVICE_H

#include <QList>

#include <entity/video.h>



class VideoService
{
public:
    VideoService();
    QList<Video> getVideoMessageService(const QString &channelName);
};

#endif // VIDEOSERVICE_H
