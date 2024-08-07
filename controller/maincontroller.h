#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include<QList>
#include"entity/video.h"
#include"entity/channel.h"
class MainController
{
public:
    MainController();
     QList<Video>getAllVideController();
     QList<Channel>getAllHotChannelController();
     void getIndexController();
     QList<Video> getVideoByChannelController(const QString &channelName);
};

#endif // MAINCONTROLLER_H
