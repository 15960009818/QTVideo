#include "channelmodel.h"
#include "util/sqliteutil.h"
#include "../entity/channel.h"
/**
 * @brief ChannelModel::ChannelModel 节目的sql编写
 */
ChannelModel::ChannelModel()
{

}

QList<Channel> ChannelModel::queryAllChannel()
{
    QList<Channel> channellist;
    char** result= nullptr;
    int row=0, col=0;
    // SQL 查询语句
    QString sql = QString("SELECT * FROM tbl_channel");

     qDebug()<<sql;
    SqliteUtil *sqliteUtil =SqliteUtil::getSqliteUtil();
    int res = sqliteUtil->querySqlite(sql,result,row,col);


    if(res == SQLITE_OK)
    {
        if(row >0)
        {

            for(int i=1;i<=row;i++)
            {

                channellist.append(Channel(atoi(result[i*col+0]),result[i*col+1]));
            }

        }

    }
    return channellist;
}
