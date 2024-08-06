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
    VerifyCode(int x, int y, int w, int h, QWidget *parent = nullptr);
    QString text() const;  // 获取当前验证码的文本
    void refresh();        // 重新生成验证码

protected:
    void paintEvent(QPaintEvent *event) override; // 绘制验证码
    void mousePressEvent(QMouseEvent *event) override; // 点击验证码重新生成

private:
    QString codeText;      // 存储验证码的文本
    void generateRandNum(); // 生成随机验证码

    int x, y, w, h;        // 验证码显示区域的参数
};

#endif // VERIFYCODE_H
