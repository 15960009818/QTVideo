#ifndef MYITEM_H
#define MYITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
class MyItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
private:
    int status;
    QPixmap img;
public:
    MyItem(QString imgPath,int status);
    //返回当前坐标
    QRectF boundingRect() const;
    //绘制方法
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option
               ,QWidget *wideget);
    //控制图元的移动
    void advance(int phase);
signals:
    void open();
public slots:
};

#endif // MYITEM_H
