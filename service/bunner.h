#ifndef BUNNER_H
#define BUNNER_H

#include <QString>
class Bunner
{
private:
    int bunnerId;
    QString bunnername;
    QString imgPath;
public:
    Bunner();
    Bunner(int bunnerId,QString bunnername,QString imgPath);
    int getBunnerId() const;
    void setBunnerId(int value);
    QString getBunnername() const;
    void setBunnername(const QString &value);
    QString getImgPath() const;
    void setImgPath(const QString &value);
};

#endif // BUNNER_H
