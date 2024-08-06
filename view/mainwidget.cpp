#include "mainwidget.h"
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
    // 创建左侧主部件
    leftWidget = new QWidget(this);
    leftLayout = new QVBoxLayout(leftWidget);
    leftWidget->setStyleSheet("background-color:white");  // 设置左侧部件的背景颜色为白色

    // 添加 logo 标签
    QLabel *logoLab = new QLabel();
    logoLab->setPixmap(QPixmap(":/image/logo.png").scaled(40, 40));  // 设置 logo 图片并调整大小
    leftLayout->addWidget(logoLab);  // 将 logo 标签添加到左侧布局

    // 创建频道列表部件
    QListWidget *channels = new QListWidget();

    // 添加固定的频道列表项
    QListWidgetItem *item1 = new QListWidgetItem(QIcon(":/image/首页.png"), "首页");
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(":/image/热点.png"), "热点");
    QListWidgetItem *item3 = new QListWidgetItem(QIcon(":/image/电视剧.png"), "电视剧");
    channels->addItem(item1);  // 添加“首页”频道
    channels->addItem(item2);  // 添加“热点”频道
    channels->addItem(item3);  // 添加“电视剧”频道

    // 添加“频道”标签
    QLabel *channelLab = new QLabel("频道");
    QListWidgetItem *labelItem = new QListWidgetItem(channels);  // 创建一个新的列表项
    int insertPosition = 4;  // 插入位置
    channels->insertItem(insertPosition, labelItem);  // 在指定位置插入列表项
    channels->setItemWidget(labelItem, channelLab);  // 将列表项设置为“频道”标签

    // 创建一个新的频道列表部件
    channelListWidget = new QListWidget;

    // 获取所有频道数据
    ChannelController channelController;
    QList<Channel> channelList = channelController.getAllChannel();

    // 遍历频道列表，添加每个频道到列表部件中
    for(int i = 0; i < channelList.size(); ++i)
    {
        Channel channel = channelList.at(i);
        QString iconPath = QString(":/image/%1.png").arg(channel.getChannelname());  // 根据频道名称生成图标路径
        qDebug() << iconPath;  // 输出图标路径调试信息
        QListWidgetItem *item = new QListWidgetItem(QIcon(iconPath), channel.getChannelname());  // 创建列表项并设置图标和频道名称
        channels->addItem(item);  // 将列表项添加到频道列表部件中
    }

    // 设置频道列表项的图标大小
    channels->setIconSize(QSize(50, 50));

    // 将频道列表部件添加到左侧布局中
    leftLayout->addWidget(channels);

    // 连接频道列表项点击信号到相应的槽函数
       connect(channels, &QListWidget::itemClicked, this, &MainWidget::onChannelItemClicked);
}

void MainWidget::onChannelItemClicked(QListWidgetItem *item)
{
    QString channelName = item->text();

    if (channelName == "首页") {
        IndexController indexController;
        indexController.execute();
    } else if (channelName == "热点") {
        HotVideoController hotVideoController;
        hotVideoController.execute();
    } else if (channelName == "电视剧") {
        VideoController videoController;
        videoController.execute();
    } else {
        // 处理其他频道的点击事件
        ChannelController channelController;
        channelController.execute(channelName);
    }
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
