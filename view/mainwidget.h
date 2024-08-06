#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <view/loginwidget.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include <service/bunner.h>
#include <QList>
#include <QListWidgetItem>
#include <QListWidget>
class MainWidget : public QWidget
{
    Q_OBJECT
private:
   QList<Bunner>hotVideoList;
   QLabel *bunnerLab ;
   LoginWidget *loginwidget;
   QWidget *leftWidget;
   QWidget *rightWidget;
   QHBoxLayout *mainLayout;
   QVBoxLayout *leftLayout;
   QVBoxLayout *rightLayout;
   QListWidget *bunnerList;
   QListWidget *videoListWidget;
   QListWidget *channelListWidget;
   QPushButton *loginButton;
   QPushButton *registerButton;
   QPushButton *cancelButton;
   QLabel *backgroundLabel;
   QLineEdit *edit;
   QPushButton *searchBtn;
public:
   MainWidget(QWidget *parent = nullptr);
   void initAllWidget();
   void initQss();//初始化所有样式
   void initAllConnet();
   void initleftWin();
   void initRightWin();
   void initNavWin();
   void initHotVideoWin();
   void initVideoListWin();
   void initData();

signals:

public slots:
   void gotoLogin();
   void changeBunner(QListWidgetItem *item);
   void updateBunner();
   void onVideoItemClicked(QListWidgetItem *item);
   void login(UserInfo userInfo);

};

#endif // MAINWIDGET_H
