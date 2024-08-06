#include "verifycode.h"
#include <QTime>
#include <QChar>
#include <QPainter>
#include <QtGlobal>

VerifyCode::VerifyCode(int x, int y, int w, int h)
{
    //验证码窗口初始化
    this->setFixedSize(w,h);
    this->setStyleSheet("background-color:white;");
    this->setLineWidth(1);
    this->setMidLineWidth(2);
    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Raised);
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->cutcode ="";
    //随机数种子初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //生成随机数
    this->generateRandNum();

}

void VerifyCode::generateRandNum()
{
    this->text.clear();
    for(int i=0;i<4;++i)
    {
        int num = qrand()%3;
        if(num == 0)
        {
            //数字
            this->text+=QString::number(qrand()%10);
        }
        else if(num == 1)
        {
            //大写字母
            int temp = 'A';
            this->text+=static_cast<QChar>(temp + qrand()%26);
        }
        else if(num == 2)
        {
            //小写字母
            int temp = 'a';
            this->text+=static_cast<QChar>(temp + qrand()%26);
        }
    }
}

void VerifyCode::paintEvent(QPaintEvent *ev)
{
    //绘图
    QPainter painter(this);
    //绘线
    QPen pen;
    QFont font("楷体",22,QFont::Bold,true);
    painter.setFont(font);
    this->setGeometry(x,y,w,h);
    //画点
    for(int i=0;i<100;++i){
        //设置随机颜色
        pen = QPen(QColor(qrand()%256,qrand()%256,qrand()%256));
        //将画笔设置为创建的随机颜色画笔
        painter.setPen(pen);
        //在（0~179,0~79）随机位置绘制
        painter.drawPoint(qrand()%w,qrand()%h);
    }

    //画线
    for(int i=0;i<5;++i){
        //设置随机颜色
        pen = QPen(QColor(qrand()%256,qrand()%256,qrand()%256));
        //将画笔设置为创建的随机颜色画笔
        painter.setPen(pen);
        //绘线（x1,y1,x2,y2）;
        painter.drawLine(qrand()%w,qrand()%h,qrand()%w,qrand()%h);
    }

    //绘制验证码
    for(int i=0;i<4;++i){
        //设置随机颜色
        pen = QPen(QColor(qrand()%256,qrand()%256,qrand()%256));
        //将画笔设置为创建的随机颜色画笔
        painter.setPen(pen);
        painter.drawText((this->w/5-3)*i,qrand()%(this->h-(this->h/2+2)),this->w/2+2,this->h/2+2,Qt::AlignCenter,QString(text[i]));
    }
    //cutcode = code;
    //QWidget::paintEvent(ev);
}
void VerifyCode::mousePressEvent(QMouseEvent *)
{
    //重新生成验证码
    generateRandNum();

    //实时更新
    update();

}

void VerifyCode::refresh()
{
    //重新生成验证码
    generateRandNum();

    //实时更新
    update();
}
