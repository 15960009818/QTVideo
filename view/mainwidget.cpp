#include "mainwidget.h"
#include <QListWidgetItem>
#include <QListWidget>
#include <QIcon>
#include <QDebug>
#include <QTimer>
#include "view/videoplayer.h"
#include "controller/channelcontroller.h"
#include "service/channel.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("主窗口");
    this->resize(1200,700);
    this->loginwidget= new LoginWidget();
    this->initData();
    this->initAllWidget();
    this->initQss();
    this->initAllConnet();
}

void MainWidget::initAllWidget()
{
    mainLayout = new QHBoxLayout(this);
    this->initleftWin();
    this->initRightWin();
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(leftWidget,2);
    contentLayout->addWidget(rightWidget,7);
    mainLayout->addLayout(contentLayout);
}

void MainWidget::initQss()
{
    QFile file(":/qss/mainwidget.qss");
    if(file.open(QFile::ReadOnly))//以只读方式打开文件
    {
        this->setStyleSheet(file.readAll());//为当前窗口中的所有组件进行养样式的设置
    }
}

void MainWidget::initAllConnet()
{
    connect(loginButton, &QPushButton::clicked, this, &MainWidget::gotoLogin);
    connect(this->bunnerList,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(changeBunner(QListWidgetItem *)));
    QTimer *timer = new QTimer;
    timer->start(2000);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateBunner()));
    connect(this->loginwidget,SIGNAL(backtoMain()),this,SLOT(show()));
    connect(this->loginwidget,SIGNAL(loginSuccessful(UserInfo)),this,SLOT(login(UserInfo)));

}

void MainWidget::initleftWin()
{
    leftWidget = new QWidget(this);
    leftLayout = new QVBoxLayout(leftWidget);
    leftWidget->setStyleSheet("background-color:white");
    QLabel *logoLab=new QLabel();
    logoLab->setPixmap(QPixmap(":/image/logo.png").scaled(40,40));
    QListWidget *channels = new QListWidget();
    QListWidgetItem *item1 = new QListWidgetItem(QIcon("://image/首页.png"),"首页");
    QListWidgetItem *item2 = new QListWidgetItem(QIcon("://image/热点.png"),"热点");
    QListWidgetItem *item3 = new QListWidgetItem(QIcon("://image/电视剧.png"),"电视剧");
    channels->addItem(item1);
    channels->addItem(item2);
    channels->addItem(item3);
    leftLayout->addWidget(logoLab);
    QLabel *channelLab=new QLabel("频道");
    QListWidgetItem *labelItem = new QListWidgetItem(channels);
    int insertPosition = 4;
    channels->insertItem(insertPosition, labelItem);
    channels->setItemWidget(labelItem, channelLab);



    channelListWidget= new QListWidget;
    ChannelController channelController;
    QList<Channel> channelList=channelController.getAllChannel();
    for(int i=0;i<channelList.size();++i)
    {
        Channel channel =channelList.at(i);
        QString iconPath=QString(":/image/%1.png").arg(channel.getChannelname());
         qDebug()<<iconPath;
        QListWidgetItem *item = new QListWidgetItem(QIcon(iconPath)
                                                    ,channel.getChannelname());
        channels->addItem(item);
    }
    channels->setIconSize(QSize(50,50));
    leftLayout->addWidget(channels);
}

void MainWidget::initRightWin()
{
    rightWidget = new QWidget(this);
    rightLayout = new QVBoxLayout(rightWidget);
    rightWidget->setStyleSheet("background-color:grey");
    this->initNavWin();
    this->initHotVideoWin();
    this->initVideoListWin();
}

void MainWidget::initNavWin()
{
    QWidget *navWidget= new QWidget;

    QHBoxLayout *navLayout = new QHBoxLayout;
    navWidget->setLayout(navLayout);
    //编辑框
    edit = new QLineEdit;
     //搜索按钮
    searchBtn = new QPushButton("搜索");
    loginButton = new QPushButton("登录");

    loginButton->setIcon(QIcon(":/image/login.png"));
    loginButton->setIconSize(QSize(30, 30));
    navLayout->addStretch(1);
    navLayout->addWidget(edit);
    navLayout->addWidget(searchBtn);
    navLayout->addStretch(2);
    navLayout->addWidget(loginButton);
    this->rightLayout->addWidget(navWidget,1);
}

void MainWidget::initHotVideoWin()
{

    QWidget *hotVideoWin = new QWidget(this);

    QHBoxLayout *bannerLayout = new QHBoxLayout;
    hotVideoWin->setLayout(bannerLayout);
    bunnerLab = new QLabel;
    bunnerLab->setMaximumSize(700,500);
    QPixmap pixmap(":/image/bunner1.jpg");
    QPixmap scaledPixmap = pixmap.scaled(bunnerLab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    bunnerLab->setPixmap(scaledPixmap);
    bunnerList= new QListWidget;
    for(int i=0; i< this->hotVideoList.size();i++){
        Bunner bunner=this->hotVideoList.at(i);
        QListWidgetItem *item = new QListWidgetItem(bunner.getBunnername());
        QFont font = item->font();
        font.setPointSize(22);
        item->setFont(font);
        //内部自带了数据域
        item->setData(Qt::UserRole,i);
        bunnerList->addItem(item);
    }

    bannerLayout->addWidget(bunnerLab,8);
    bannerLayout->addWidget(bunnerList,2);
    bannerLayout->addStretch(2);
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    rightLayout->addWidget(hotVideoWin,3);
}

void MainWidget::initVideoListWin()
{

    QWidget *videoListWin = new QWidget(this);
    videoListWin->setStyleSheet("background-color:gray");
    QHBoxLayout *videoLayout = new QHBoxLayout;
    videoListWin->setLayout(videoLayout);
    videoListWidget = new QListWidget;
    QListWidgetItem *item1= new QListWidgetItem(QIcon(":/image/bunner1.jpg"),"视频1");
    item1->setData(Qt::UserRole, "video/video1.mp4"); // 存储视频路径
    videoListWidget->addItem(item1);
    QListWidgetItem *item2= new QListWidgetItem(QIcon(":/image/bunner2.jpg"),"视频2");
    videoListWidget->addItem(item2);
    QListWidgetItem *item3= new QListWidgetItem(QIcon(":/image/bunner3.jpg"),"视频3");
    videoListWidget->addItem(item3);
    QListWidgetItem *item4= new QListWidgetItem(QIcon(":/image/bunner1.jpg"),"视频4");
    videoListWidget->addItem(item4);
    QListWidgetItem *item5= new QListWidgetItem(QIcon(":/image/bunner2.jpg"),"视频5");
    videoListWidget->addItem(item5);
    //图标模式
    videoListWidget->setViewMode(QListView::IconMode);
    videoListWidget->setIconSize(QSize(200,200));
    videoListWidget->setResizeMode(QListView::Adjust);
    videoListWidget->setSpacing(10);
    //固定图标位置
    videoListWidget->setMovement(QListView::Static);
    connect(videoListWidget, &QListWidget::itemClicked, this, &MainWidget::onVideoItemClicked);
    videoLayout->addWidget(videoListWidget);
    rightLayout->addWidget(videoListWin,4);
}

void MainWidget::initData()
{

    this->hotVideoList.append(Bunner(1,"bunner1","://image/bunner1.jpg"));
    this->hotVideoList.append(Bunner(2,"bunner2","://image/bunner2.jpg"));
    this->hotVideoList.append(Bunner(3,"bunner3","://image/bunner3.jpg"));
}

void MainWidget::changeBunner(QListWidgetItem *item)
{
    Bunner bunner = this->hotVideoList.at(item->data(Qt::UserRole).toInt());
    QPixmap pixmap(QPixmap(bunner.getImgPath()));
    QPixmap scaledPixmap = pixmap.scaled(bunnerLab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    bunnerLab->setPixmap(scaledPixmap);
//    for(int i = 0; i < this->hotVideoList.size(); ++i)
//    {
//        Bunner bunner = this->hotVideoList.at(i);

//        if(bunner.getBunnername() == item->text())
//        {
//            QPixmap pixmap(QPixmap(bunner.getImgPath()));
//            QPixmap scaledPixmap = pixmap.scaled(bunnerLab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//            bunnerLab->setPixmap(scaledPixmap);
//        }
    //    }
}

void MainWidget::updateBunner()
{
    int currentIndex = bunnerList->currentRow();
    int index=++currentIndex%this->hotVideoList.size();
    Bunner bunner = this->hotVideoList.at(index);
    QPixmap pixmap(QPixmap(bunner.getImgPath()));
    QPixmap scaledPixmap = pixmap.scaled(bunnerLab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    bunnerLab->setPixmap(scaledPixmap);
    // 选中 QListWidget 中的相关项
    QListWidgetItem* item = bunnerList->item(index);
    bunnerList->setCurrentItem(item);
}
void MainWidget::gotoLogin()
{
    this->hide();
    loginwidget->show();
}
void MainWidget::onVideoItemClicked(QListWidgetItem *item) {
    QString videoPath = item->data(Qt::UserRole).toString();
    qDebug()<<videoPath;
    if (!videoPath.isEmpty()) {
        VideoPlayer *player = new VideoPlayer;
        player->setAttribute(Qt::WA_DeleteOnClose);
        player->resize(800, 600);
        player->show();
        player->playVideo(videoPath);
    }
}

void MainWidget::login(UserInfo userInfo)
{
    loginButton->setText(userInfo.getUserName());
}
