#ifndef CHANNEL_H
#define CHANNEL_H
#include <QString>

class Channel
{
private:
    int channelId;
    QString channelname;
public:
    Channel();
    Channel(int channelId,QString channelname);
    int getChannelId() const;
    void setChannelId(int value);
    QString getChannelname() const;
    void setChannelname(const QString &value);
};

#endif // CHANNEL_H
