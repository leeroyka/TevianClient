#ifndef TEVIANCLIENT_DOMAIN_FACE_HPP
#define TEVIANCLIENT_DOMAIN_FACE_HPP

#include <QString>

namespace Domain {

class Face
{
public:
  Face(qint32 x, qint32 y, qint32 height, qint32 width);
  void setGender(QString gender);
  void setAge(qreal mean, qreal variance);

private:
  qint32  mX;
  qint32  mY;
  qint32  mheight;
  qint32  mWidth;
  QString mGender;
  qreal   mAge;
  qreal   mVarianceAge;
};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_FACE_HPP
