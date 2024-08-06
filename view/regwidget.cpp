#include "regwidget.h"
#include "loginwidget.h"
#include "util/sqliteutil.h"
#include "controller/usercontroller.h"
RegWidget::RegWidget(QWidget *parent)
    : QWidget(parent)
{
    this->initAllWidget();
    this->initQss();
    this->initAllConnet();
}

RegWidget::~RegWidget()
{

}
void RegWidget::initAllWidget()
{
    setWindowTitle("注册界面");
    setWindowIcon(QIcon(":/image/player.png"));
    setFixedSize(400, 400);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/image/bg.jpg")));
    this->setPalette(palette);

    QLabel *usernameLabel = new QLabel("用户名:", this);
    usernameLabel->setGeometry(50, 50, 80, 30);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("请输入用户名");
    usernameEdit->setMaxLength(12);
    usernameEdit->setGeometry(140, 50, 180, 30);

    QLabel *passwordLabel = new QLabel("密码:", this);
    passwordLabel->setGeometry(50, 100, 80, 30);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setMaxLength(10);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setGeometry(140, 100, 180, 30);

    QLabel *confirmPasswordLabel = new QLabel("确认密码:", this);
    confirmPasswordLabel->setGeometry(50, 150, 80, 30);
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("请确认密码");
    confirmPasswordEdit->setMaxLength(10);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setGeometry(140, 150, 180, 30);

    QLabel *idTypeLabel = new QLabel("证件类型:", this);
    idTypeLabel->setGeometry(50, 200, 80, 30);
    idTypeComboBox = new QComboBox(this);
    idTypeComboBox->addItem("身份证");
    idTypeComboBox->addItem("学生证");
    idTypeComboBox->setGeometry(140, 200, 180, 30);

    QLabel *hobbiesLabel = new QLabel("爱好:", this);
    hobbiesLabel->setGeometry(50, 250, 80, 30);
    hikingCheckBox = new QCheckBox("爬山", this);
    hikingCheckBox->setGeometry(140, 250, 80, 30);
    swimmingCheckBox = new QCheckBox("游泳", this);
    swimmingCheckBox->setGeometry(220, 250, 80, 30);
    runningCheckBox = new QCheckBox("跑步", this);
    runningCheckBox->setGeometry(300, 250, 80, 30);

    registerButton = new QPushButton("注册", this);
    registerButton->setGeometry(120, 320, 80, 30);
    cancelButton = new QPushButton("取消", this);
    cancelButton->setGeometry(220, 320, 80, 30);

}

void RegWidget::initQss()
{

}

void RegWidget::initAllConnet()
{
    connect(registerButton, &QPushButton::clicked, this, &RegWidget::registerUser);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(gotoLoginWin()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(clearAllEdits()));
}

void RegWidget::registerUser()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();
    QString idType = idTypeComboBox->currentText();
    QStringList hobbies;

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请填写完整信息！");
        return;
    }

    if (username.length() < 6 || username.length() > 12) {
        QMessageBox::warning(this, "输入错误", "用户名长度应在6到12位之间！");
        return;
    }

    if (password.length() < 6 || password.length() > 10) {
        QMessageBox::warning(this, "输入错误", "密码长度应在6到10位之间！");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "输入错误", "两次输入的密码不一致！");
        return;
    }

    if (hikingCheckBox->isChecked()) {
        hobbies.append("爬山");
    }
    if (swimmingCheckBox->isChecked()) {
        hobbies.append("游泳");
    }
    if (runningCheckBox->isChecked()) {
        hobbies.append("跑步");
    }

    UserController userController ;
    int res=userController.regService(username,password);

    if(res==1)
    {
        qDebug()<<"注册成功";
        QMessageBox::information(this, "注册成功！", "注册成功！！");
        this->gotoLoginWin();
    }
    else if(res == 0)
    {
        QMessageBox::warning(this, "警告","用户名重复");
    }





}

void RegWidget::gotoLoginWin()
{
    this->hide();
    //trimmed()去除前后空格
    QString username=this->usernameEdit->text().trimmed();//获取输入用户名
    emit backtoLogin(username);//注册窗口登陆窗口发信号

}

void RegWidget::clearAllEdits()
{
    // 获取所有子控件中的QLineEdit

    QList<QLineEdit *> lineEdits = findChildren<QLineEdit *>();
    for (QLineEdit *lineEdit : lineEdits) {
        lineEdit->clear();
    }
    idTypeComboBox->setCurrentIndex(0);
    QList<QCheckBox *> checkBoxes = findChildren<QCheckBox *>();
    // 取消所有QCheckBox的勾选
    for (QCheckBox *checkBox : checkBoxes) {
        checkBox->setChecked(false);
    }


}


void RegWidget::closeEvent(QCloseEvent *event)
{
    emit backtoLogin();
    //clearAllEdits();
}


