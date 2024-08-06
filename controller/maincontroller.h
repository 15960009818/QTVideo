#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include<QList>
#include"service/video.h"
#include"service/channel.h"
class MainController
{
public:
    MainController();
     QList<Video>getAllVideController();
     QList<Channel>getAllHotChannelController();
     void getIndexController();
};

#endif // MAINCONTROLLER_H
