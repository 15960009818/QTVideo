#include "verifycode.h"
#include <QTime>
#include <QChar>
#include <QPainter>
#include <QtGlobal>

// VerifyCode 构造函数
VerifyCode::VerifyCode(int x, int y, int w, int h)
    : x(x), y(y), w(w), h(h), verifyCode("")
{
    // 验证码窗口初始化
    this->setFixedSize(w, h);
    this->setStyleSheet("background-color:white;");
    this->setLineWidth(1);
    this->setMidLineWidth(2);
    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Raised);

    // 随机数种子初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    // 生成随机数
    this->generateRandNum();
}

// 生成随机验证码
void VerifyCode::generateRandNum()
{
    verifyCode.clear();  // 清空之前的验证码

    for (int i = 0; i < 4; ++i) {
        int num = qrand() % 3;
        if (num == 0) {
            // 数字
            verifyCode += QString::number(qrand() % 10);
        } else if (num == 1) {
            // 大写字母
            int temp = 'A';
            verifyCode += static_cast<QChar>(temp + qrand() % 26);
        } else if (num == 2) {
            // 小写字母
            int temp = 'a';
            verifyCode += static_cast<QChar>(temp + qrand() % 26);
        }
    }
}

// 获取验证码文本
QString VerifyCode::getVerifyCode() const
{
    return verifyCode;
}

// 绘制事件处理
void VerifyCode::paintEvent(QPaintEvent *ev)
{
    // 绘图
    QPainter painter(this);
    QPen pen;
    QFont font("楷体", 22, QFont::Bold, true);
    painter.setFont(font);
    this->setGeometry(x, y, w, h);

    // 画点
    for (int i = 0; i < 100; ++i) {
        // 设置随机颜色
        pen = QPen(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        // 将画笔设置为创建的随机颜色画笔
        painter.setPen(pen);
        // 在（0~w-1, 0~h-1）随机位置绘制
        painter.drawPoint(qrand() % w, qrand() % h);
    }

    // 画线
    for (int i = 0; i < 5; ++i) {
        // 设置随机颜色
        pen = QPen(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        // 将画笔设置为创建的随机颜色画笔
        painter.setPen(pen);
        // 绘线（x1, y1, x2, y2）
        painter.drawLine(qrand() % w, qrand() % h, qrand() % w, qrand() % h);
    }

    // 绘制验证码
    for (int i = 0; i < 4; ++i) {
        // 设置随机颜色
        pen = QPen(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        // 将画笔设置为创建的随机颜色画笔
        painter.setPen(pen);
        // 绘制验证码字符
           painter.drawText((this->w / 5) * i + 10, qrand() % (this->h - 20) + 30, QString(verifyCode[i]));
    }

    QWidget::paintEvent(ev);
}

// 鼠标点击事件处理
void VerifyCode::mousePressEvent(QMouseEvent *)
{
    // 重新生成验证码
    generateRandNum();
    // 实时更新
    update();
}

// 刷新验证码
void VerifyCode::refresh()
{
    // 重新生成验证码
    generateRandNum();
    // 实时更新
    update();
}
