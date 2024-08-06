#include "channelcontroller.h"
#include "service/channelmodel.h"
ChannelController::ChannelController()
{

}

QList<Channel> ChannelController::getAllChannel()
{
    ChannelModel channelModel;
    return channelModel.queryAllChannel();
}
