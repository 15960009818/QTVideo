#include "usercontroller.h"
#include "service/usermodel.h"
#include "view/loginwidget.h"
#include "service/verifycode.h"
#include <QString>
#include <QtDebug>
UserController::UserController()
{

}

int UserController::loginController(const QString &username, const QString &password, const QString &captcha) {
    // 1. 检查账号、密码和验证码是否为空
        if (username.isEmpty() || password.isEmpty()) {
            return 0;  // 账号或密码为空
        }

        // 2. 验证码检查
        if (captcha.toLower() != VerifyCode->text.toLower()) {
            return -1;  // 验证码错误
        }

        // 3. 数据库匹配

        // 这里假设用户名和密码的验证逻辑
        // 实际应用中会通过数据库查询来验证用户名和密码
        // 例如：查找数据库中的用户记录进行匹配
        if (username == "user" && password == "pass") {
            return 1;  // 登录成功
        } else {
            return 0;  // 登录失败
        }
}


int UserController::loginService(QString username, QString password)
{
    UserModel userMdodel;
    return userMdodel.queryUserByNamePwd(username,password);
}

int UserController::regService(QString username, QString password)
{
    UserModel userMdodel;
     // 检查用户名是否已存在
    int res =userMdodel.queryUserByName(username);
    if(res == 1)
    {
        return 0;
    }
    //添加用户
    return userMdodel.addUserByNamePwd(username,password);

}
