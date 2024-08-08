#include "maincontroller.h"
#include<QList>
MainController::MainController(QObject* parent):QObject (parent)
{

}

int MainController::add(int a, int b)
{
    return a+b;
}

//QList<Video> MainController::getVideoByChannelController(const QString &channelName)
//{
//    VideoService videoService;
//    return videoService.getVideoMessageService(channelName);
//}

