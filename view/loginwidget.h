#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>
#include <QPixmap>
#include <QFile>
#include <QMessageBox>
#include "view/regwidget.h"
#include "entity/userinfo.h"
#include "util/verifycode.h"
class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
public:
    void initAllWidget();
    void initQss();//初始化所有样式
    void initAllConnet();
    QString getUsername() const;
    QString getPassword() const;
    QString getCaptcha() const;
signals:
    void backtoMain();
    void loginSuccessful(UserInfo);
public slots:
    void openRegistration();//打开注册窗口
    void login();//登陆验证
    void backtoLoginWin(QString);
    void gotoMainWin();
    void clearAllEdits();
protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event) ; // 重载窗口关闭事件
private:
    QLineEdit *usernameEdit;
    QLineEdit *captchaEdit;
    QLineEdit *passwordEdit;

    QPushButton *loginButton;
    QPushButton *exitButton;
    QPushButton *registerButton;
    QPushButton *cancelButton;
    VerifyCode *code;
    RegWidget *regwidget;


};

#endif // LOGINWIDGET_H
