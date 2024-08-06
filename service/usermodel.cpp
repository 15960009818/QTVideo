#include "service/usermodel.h"
#include <QDebug>
#include "util/sqliteutil.h"

UserModel::UserModel()
{

}

int UserModel::queryUserByNamePwd(QString username, QString password)
{

    char** result= nullptr;
    int row=0, col=0;
    // SQL 查询语句
    QString sql = QString("SELECT * FROM tbl_user WHERE user_name = '%1' AND user_pwd = '%2'")
                      .arg(username)
                      .arg(password);
     qDebug()<<sql;
    SqliteUtil *sqliteUtil =SqliteUtil::getSqliteUtil();
    int res = sqliteUtil->querySqlite(sql,result,row,col);


    if(res == SQLITE_OK)
    {
        if(row >0)
        {
            return 1;
        }

    }
    return -1;
}

int UserModel::queryUserByName(QString username)
{
    char** result= nullptr;
    int row=0, col=0;
    // SQL 查询语句
    QString sql = QString("SELECT * FROM tbl_user WHERE user_name = '%1'")
                      .arg(username);
     qDebug()<<sql;
    SqliteUtil *sqliteUtil =SqliteUtil::getSqliteUtil();
    int res = sqliteUtil->querySqlite(sql,result,row,col);


    if(res == SQLITE_OK)
    {
        if(row >0)
        {
            return 1;
        }

    }
    return -1;
}

int UserModel::addUserByNamePwd(QString username, QString password)
{

    QString sql = QString("insert into tbl_user (user_name,user_pwd)values('%1','%2')")
                 .arg(username)
                 .arg(password);
    qDebug()<<sql;
    SqliteUtil *sqliteUtil =SqliteUtil::getSqliteUtil();
    int res = sqliteUtil->updateSqlite(sql);
    if (res == SQLITE_OK)
    {
       return 1;
    }
    return -1;
}
