#include "maincontroller.h"
#include "videoservice.h"

#include <service/channelmodel.h>

MainController::MainController()
{

}

QList<Video> MainController::getVideoByChannelController(const QString &channelName)
{
    VideoService videoService;
    return videoService.getVideoMessageService(channelName);
}

