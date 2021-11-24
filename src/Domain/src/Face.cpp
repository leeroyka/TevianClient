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


