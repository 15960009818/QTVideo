#include "bunner.h"

int Bunner::getBunnerId() const
{
    return bunnerId;
}

void Bunner::setBunnerId(int value)
{
    bunnerId = value;
}

QString Bunner::getBunnername() const
{
    return bunnername;
}

void Bunner::setBunnername(const QString &value)
{
    bunnername = value;
}

QString Bunner::getImgPath() const
{
    return imgPath;
}

void Bunner::setImgPath(const QString &value)
{
    imgPath = value;
}

Bunner::Bunner()
{

}

Bunner::Bunner(int bunnerId, QString bunnername, QString imgPath)
{
    this->bunnerId=bunnerId;
    this->bunnername=bunnername;
    this->imgPath=imgPath;
}
