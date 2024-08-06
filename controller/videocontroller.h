#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H
#include <QList>
#include "service/video.h"
class VideoController
{
public:
    VideoController();
    QList<Video>getHotVideos();
};

#endif // VIDEOCONTROLLER_H
