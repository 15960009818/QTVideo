#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H
#include <QList>
#include "channel.h"
class ChannelModel
{
public:
    ChannelModel();
    QList<Channel>queryAllChannel();
};

#endif // CHANNELMODEL_H
