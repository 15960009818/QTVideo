#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

class MainController:public QObject
{
    Q_OBJECT

public:
    MainController(QObject* parent = nullptr);
    int add(int a,int b);
};

#endif // MAINCONTROLLER_H
