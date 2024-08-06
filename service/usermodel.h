#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>
/**
 * @brief The UserModel class
 * 实现用户的数据库相关操作（操作用户表）
 */
class UserModel
{
public:
    UserModel();
    int queryUserByNamePwd(QString username,QString password);//返回值为1表示用户名密码正确，其他为错误
    int queryUserByName(QString username);//返回值为1表示用户名密码正确，其他为错误
    int addUserByNamePwd(QString username,QString password);//返回值为1表示用户添加成功，其他为错误
};

#endif // USERMODEL_H
