#include "videocontroller.h"
#include "util/sqliteutil.h"

VideoController::VideoController()
{

}

QList<Video> VideoController::getHotVideos()
{
    //查询热门视频
    QString sql =QString();
    char **result=nullptr;
    int row=0,col=0;
    SqliteUtil::getSqliteUtil()->querySqlite(sql,result,row,col);
    //创建一个qlist的容器，将查询结果保存到容器中
    QList<Video>hotVideosList;
    return hotVideosList;
}

