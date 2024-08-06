#include "sqliteutil.h"

SqliteUtil::SqliteUtil()
{
    int res = sqlite3_open("video2.db",&pdb);
    if(res != SQLITE_OK)
    {
        qDebug()<<sqlite3_errcode(pdb);//输出错误代码
        qDebug()<< sqlite3_errmsg(pdb);//输出错误信息
    }
    qDebug()<<"连接数据库";
}

SqliteUtil::~SqliteUtil()
{
    sqlite3_close(pdb);
}

SqliteUtil* SqliteUtil::sqliteUtil= nullptr;


SqliteUtil* SqliteUtil::getSqliteUtil()
{
    if(sqliteUtil == nullptr)
    {
        sqliteUtil = new SqliteUtil();
    }
    return sqliteUtil ;
}

int SqliteUtil::updateSqlite(QString sql)
{
    int res = 0;
    char *errMsg = nullptr;
    qDebug()<< sql;
    res = sqlite3_exec(pdb,sql.toUtf8(),nullptr,nullptr,&errMsg);
    if(res != SQLITE_OK)
    {
        qDebug()<< errMsg;
    }
    return res;
}

int SqliteUtil::querySqlite(QString sql, char **&result, int &row, int &col)
{
    int res = 0;
    char *errMsg = nullptr;
    qDebug()<< sql;
    res = sqlite3_get_table(pdb,sql.toUtf8(),&result,&row,&col,&errMsg);
    if(res != SQLITE_OK)
        qDebug() << errMsg;
    return res;
}
