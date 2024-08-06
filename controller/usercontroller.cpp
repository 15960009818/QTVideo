#include "usercontroller.h"
#include "service/usermodel.h"
#include "util/verifycode.h"
#include <QString>
#include <QtDebug>
#define verifyCodeError -1
#define loginSuccess 1
#define loginFail 0
#define usernameOrPasswordIsNull -2
UserController::UserController(){

}


/**
 * @brief UserController::loginController 登录controller
 * @param username 用户账号QString
 * @param password 用户密码QString
 * @param captcha 用户输入验证码QString
 * @param verifyCode 生成的验证码QString
 * @return
 */
int UserController::loginController(const QString &username, const QString &password, const QString &captcha, const QString &verifyCode) {
    // 1. 检查账号、密码和验证码是否为空
        if (username.isEmpty() || password.isEmpty()) {
            return usernameOrPasswordIsNull;  // 账号或密码为空
        }

        // 2. 验证码检查
        if (captcha.toLower() != verifyCode.toLower()) {
            return verifyCodeError;  // 验证码错误
        }

    // 3. 数据库验证
    int res = loginService(username , password);
    if(res == loginSuccess){
          return loginSuccess;  // 登录成功
    }else {
          return loginFail;  // 登录失败
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
