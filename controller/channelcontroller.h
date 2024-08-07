#ifndef CHANNELCONTROLLER_H
#define CHANNELCONTROLLER_H
#include <QList>
#include "entity/channel.h"
/**
 * @brief The ChannelController class
 *
 */
class ChannelController
{
public:
    ChannelController();
    QList<Channel>getAllChannel();
};

#endif // CHANNELCONTROLLER_H
