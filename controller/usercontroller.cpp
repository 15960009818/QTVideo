#include "usercontroller.h"
#include "service/usermodel.h"
UserController::UserController()
{

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
