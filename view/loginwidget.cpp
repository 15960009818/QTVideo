#include "loginwidget.h"
#include <QShortcut>
#include <QDebug>
#include "sqlite3.h"
#include <QVBoxLayout>
#include "util/sqliteutil.h"
#include "controller/usercontroller.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    this->regwidget= new RegWidget();
    this->initAllWidget();
    this->initQss();
    this->initAllConnet();
}

LoginWidget::~LoginWidget()
{

}

/**
 * @brief LoginWidget::initAllWidget 登录页面
 */
void LoginWidget::initAllWidget()
{
    setWindowTitle("登录界面");
    setWindowIcon(QIcon(":/image/player.png"));
    resize(560, 400);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/bg.jpg")));
    this->setPalette(palette);

    // 账号部分
    QLabel *usernameLabel = new QLabel("账号:", this);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setMaxLength(12);

    QHBoxLayout *usernameLayout = new QHBoxLayout();
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);

    // 密码部分
    QLabel *passwordLabel = new QLabel("密码:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setMaxLength(10);
    passwordEdit->setEchoMode(QLineEdit::Password);

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    // 验证码部分
    QLabel *captchaPromptLabel = new QLabel("验证码:", this);
    captchaEdit = new QLineEdit(this);
    captchaEdit->setMaxLength(4);
    code = new VerifyCode(320, 190, 90, 40);

    QHBoxLayout *captchaLayout = new QHBoxLayout();
    captchaLayout->addWidget(captchaPromptLabel);
    captchaLayout->addWidget(captchaEdit);
    captchaLayout->addWidget(code);

    // 按钮部分
    loginButton = new QPushButton("登录", this);
    registerButton = new QPushButton("注册", this);
    cancelButton = new QPushButton("取消", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(cancelButton);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(captchaLayout);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
}

/**
 * @brief LoginWidget::initQss Qss加载
 */
void LoginWidget::initQss()
{
    QFile file(":/qss/loginwin.qss");
    if(file.open(QFile::ReadOnly))//以只读方式打开文件
    {
        this->setStyleSheet(file.readAll());//为当前窗口中的所有组件进行养样式的设置
    }

}

/**
 * @brief LoginWidget::initAllConnet 初始化槽函数
 */
void LoginWidget::initAllConnet()
{
    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::login);
    connect(registerButton, &QPushButton::clicked, this, &LoginWidget::openRegistration);
    connect(this->regwidget,SIGNAL(backtoLogin()),this,SLOT(show()));
    connect(this->regwidget,SIGNAL(backtoLogin(QString)),this,SLOT(backtoLoginWin(QString)));
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcut, &QShortcut::activated, this, &LoginWidget::login);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(gotoMainWin()));

}

void LoginWidget::login() {
    // 1. 获取用户输入
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString captcha = captchaEdit->text();
    QString generatedCaptcha = code->getVerifyCode();

    // 2. 调用控制层，获取数据
    UserController userController;
    int res = userController.loginController(username, password, captcha, generatedCaptcha);

    // 3. 处理返回结果
        if (res == 1) {
            qDebug() << "登录成功！";
            QMessageBox::information(this, "登录成功！", "登录成功！");
            code->refresh();
            this->gotoMainWin();
            UserInfo userInfo(username);
            emit loginSuccessful(userInfo);
        } else if (res == -1) {
            QMessageBox::warning(this, "错误", "验证码错误！");
            code->refresh();
        } else if(res == -2){
            QMessageBox::warning(this, "错误", "用户名或密码为空！");
            code->refresh();
        }  else if(res == 0){
            QMessageBox::warning(this, "错误", "账号或密码有误");
            code->refresh();
        }
}

void LoginWidget::backtoLoginWin(QString username)
{
    usernameEdit->setText(username);
    this->show();
}
void LoginWidget::openRegistration()
{
    this->hide();
    regwidget->show();
    clearAllEdits();
    code->update();
}
void LoginWidget::gotoMainWin()
{
    this->hide();
    code->refresh();
    clearAllEdits();
    emit backtoMain();
}

void LoginWidget::clearAllEdits()
{
    //qDebug()<<"1";
    // 获取所有子控件中的QLineEdit
    QList<QLineEdit *> lineEdits = findChildren<QLineEdit *>();
    for (QLineEdit *lineEdit : lineEdits) {
        lineEdit->clear();
    }

}


void LoginWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QPixmap pixmap(":/image/bg.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(palette);
}

void LoginWidget::closeEvent(QCloseEvent *event)
{
    emit backtoMain();
    this->clearAllEdits();
    clearAllEdits();
}




