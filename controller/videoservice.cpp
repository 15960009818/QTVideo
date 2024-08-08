#include "videoservice.h"

#include <QList>

#include <entity/video.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

VideoService::VideoService()
{

}

QList<Video> VideoService::getVideoMessageService(const QString &channelName)
{
    QList<Video> videoList;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/mnt/data/video2.db");

    if (!db.open())
    {
        qDebug() << "Failed to open database.";
        return videoList;
    }

    QSqlQuery query;
    query.prepare("SELECT video_id, video_name, video_image, video_path FROM videos WHERE channel_name = :channelName");
    query.bindValue(":channelName", channelName);

    if (query.exec())
    {
        while (query.next())
        {
            Video video;
            video.setVideoId(query.value(0).toInt());
            video.setVideoName(query.value(1).toString());
           // video.setVideoImage(query.value(2).toString());
            video.setVideoPath(query.value(3).toString());
            videoList.append(video);
        }
    }
    else
    {
        qDebug() << "Query failed: " << query.lastError();
    }

    db.close();
    return videoList;
}
