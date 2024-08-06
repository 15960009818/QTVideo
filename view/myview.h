#ifndef MYVIEW_H
#define MYVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "service/myitem.h"
#include "mainwidget.h"
#include <QTimer>
class MyView : public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene *myScene;
    MyItem *item1,*item2;
    QTimer *timer;
    MainWidget *mainwidget;
public:
    MyView();

signals:

public slots:
    void gotoMainWin();
};

#endif // MYVIEW_H
