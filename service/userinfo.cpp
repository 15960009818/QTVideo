#include "userinfo.h"

QString UserInfo::getUserName() const
{
    return userName;
}

void UserInfo::setUserName(const QString &value)
{
    userName = value;
}

UserInfo::UserInfo()
{

}

UserInfo::UserInfo(QString userName)
{
    this->userName=userName;
}
