#include "myitem.h"


MyItem::MyItem(QString imgPath, int status)
{
    this->img.load(imgPath);
    this->status=status;
}

QRectF MyItem::boundingRect() const
{
    return QRectF(-this->img.width()/2,-this->img.height()/2,
                  this->img.width(),this->img.height());
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *wideget)
{
    painter->drawPixmap(-this->img.width()/2,-this->img.height()/2,
                        this->img.width(),this->img.height(),this->img);
}

void MyItem::advance(int phase)
{
    if(this->status==1)
    {
        //向前移动一个单元
        this->setPos(this->mapToScene(1,0));
        //碰撞检测
        if(collidingItems().count()>0)
        {
            this->status=0;
            emit open();
        }
    }

}
