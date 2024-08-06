#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
class UserInfo
{
private:
    QString userName;
public:
    UserInfo();
    UserInfo(QString userName);
    QString getUserName() const;
    void setUserName(const QString &value);
};

#endif // USERINFO_H
