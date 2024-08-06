#ifndef SQLITEUTIL_H
#define SQLITEUTIL_H

#include "sqlite3.h"
#include <QDebug>
#include <QString>
class SqliteUtil
{
private:
    sqlite3 *pdb = nullptr;
    SqliteUtil();

    static SqliteUtil *sqliteUtil ;
public:
    ~SqliteUtil();
    static SqliteUtil *getSqliteUtil();
    int updateSqlite(QString sql);
    int querySqlite(QString sql, char **&result, int &row, int &col);
};

#endif // SQLITEUTIL_H
