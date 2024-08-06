#ifndef VERIFYCODE_H
#define VERIFYCODE_H


#include <QFrame>
#include <QString>
#include <QPaintEvent>
#include <QMouseEvent>

class VerifyCode : public QFrame
{
    Q_OBJECT
   public:
       VerifyCode(int x, int y, int w, int h);
       void generateRandNum();
       void paintEvent(QPaintEvent *);
       void mousePressEvent(QMouseEvent *);
       void refresh();
       QString text,cutcode;
       int x,y,w,h;
};

#endif // VERIFYCODE_H
