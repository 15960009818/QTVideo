#ifndef REGWIDGET_H
#define REGWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QString>
class RegWidget : public QWidget
{
    Q_OBJECT
public:
    RegWidget(QWidget *parent = nullptr);
    ~RegWidget();
    void initAllWidget();
    void initQss();//初始化所有样式
    void initAllConnet();
signals: //信号区（信号只需声明，无需实现）
    void backtoLogin();
    void backtoLogin(QString); //在注册窗口声明了exit的信号
public slots: //槽函数区（声明并实现）
    void registerUser();
    void gotoLoginWin();
    void clearAllEdits();
protected:
    void closeEvent(QCloseEvent *event) ; // 重载窗口关闭事件
private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;
    QComboBox *idTypeComboBox;
    QCheckBox *hikingCheckBox;
    QCheckBox *swimmingCheckBox;
    QCheckBox *runningCheckBox;
    QPushButton *registerButton;
    QPushButton *cancelButton;

};

#endif // REGWIDGET_H
