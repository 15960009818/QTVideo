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


    return a.exec();
}

