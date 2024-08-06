#include "view/mainwidget.h"
#include <QApplication>
#include <QDebug>
#include <QWidget>
#include "view/myview.h"
#include "controller/channelcontroller.h"
#include "view/loginwidget.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

   // LoginWidget w;


    MyView w;
    w.show();

    /*
    QFile file(":/video/video1.mp4");
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "Resource file loaded successfully";
        file.close();
    } else {
        qDebug() << "Failed to load resource file";
    }
    VideoPlayer *player = new VideoPlayer;
    player->setAttribute(Qt::WA_DeleteOnClose);
    player->resize(800, 600);
    player->show();
    player->playVideo(QUrl("qrc:/video/video2.mp4"));
*/

    return a.exec();
}
