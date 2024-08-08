#include "maincontroller.h"
#include "videoservice.h"
#include <qdebug.h>
#include <service/channelmodel.h>
#include <view/videoplayer.h>

MainController::MainController()
{

}

QList<Video> MainController::getVideoByChannelController(const QString &channelName)
{
    qDebug()<<"getVideoByChannelController被调用";
    VideoService videoService;

    return videoService.getVideoMessageService(channelName);
}

