#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <QString>
#include "view/loginwidget.h"
class UserController
{
public:
    UserController();
    int loginController(const QString &username, const QString &password, const QString &captcha);
    int loginService(QString username,QString password);//返回1表示登录成功
    int regService(QString username,QString password);//返回1表示注册成功 返回0表示用户已存在
};

#endif // USERCONTROLLER_H
