#include "myview.h"


MyView::MyView()
{
    mainwidget= new MainWidget;
    setWindowTitle("开机动画");
    this->setBackgroundBrush(QBrush(QPixmap("://image/愤怒的小鸟.jpg")));
    this->setFixedSize(960,600);
    //必须设置游戏的场景，背景才会显示
    this->myScene= new QGraphicsScene;
    this->setScene(myScene);
    this->setSceneRect(0,0,this->width()-2,this->height()-2);

    this->item1 = new MyItem("://image/小红.png",1);
    this->item1->setPos(120,this->height()/2);
    this->myScene->addItem(item1);
    this->item2 = new MyItem("://image/钱币.png",0);
    this->item2->setPos(900,this->height()/2);
    //将图元添加到场景中
    this->myScene->addItem(item2);



    this->timer= new QTimer();
    timer->start(5);
    connect(this->timer,SIGNAL(timeout()),this->scene(),SLOT(advance()));
    connect(item1,SIGNAL(open()),this,SLOT(gotoMainWin()));
}
void MyView::gotoMainWin()
{
    this->hide();
    this->mainwidget->show();
}
