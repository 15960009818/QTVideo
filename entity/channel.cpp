#include "channel.h"

int Channel::getChannelId() const
{
    return channelId;
}

void Channel::setChannelId(int value)
{
    channelId = value;
}

QString Channel::getChannelname() const
{
    return channelname;
}

void Channel::setChannelname(const QString &value)
{
    channelname = value;
}


Channel::Channel()
{

}

Channel::Channel(int channelId, QString channelname)
{
    this->channelId=channelId;
    this->channelname=channelname;
}
