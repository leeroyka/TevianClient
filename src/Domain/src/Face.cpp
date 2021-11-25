#include <Domain/Face.hpp>

#include <math.h>

Domain::Face::Face(qint32 x, qint32 y, qint32 height, qint32 width)
  : mX(x)
  , mY(y)
  , mheight(height)
  , mWidth(width)
  , mAge(0)
  , mGender("")
{

}

void Domain::Face::setGender(QString gender)
{
  mGender = gender;
}

void Domain::Face::setAge(qreal mean, qreal variance)
{
  mAge = mean;
  mVarianceAge = sqrt(variance);
}

qint32 Domain::Face::getX() const
{
    return mX;
}

qint32 Domain::Face::getY() const
{
    return mY;
}

qint32 Domain::Face::getHeight() const
{
    return mheight;
}

qint32 Domain::Face::getWidth() const
{
    return mWidth;
}

QString Domain::Face::getGender() const
{
    return mGender;
}

QString Domain::Face::getAge() const
{
    return QString(QString::number(mAge)+0x00B1+QString::number(mVarianceAge));
}


