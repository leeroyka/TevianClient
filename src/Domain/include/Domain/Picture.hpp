#ifndef TEVIANCLIENT_DOMAIN_PICTURE_HPP
#define TEVIANCLIENT_DOMAIN_PICTURE_HPP

#include <Domain/Face.hpp>

#include <QVector>

#include <memory>

namespace Domain {

class Picture
{
public:
  Picture();

  //addFace
  //getFaces
  //set
  //get
  QString getPictureName() const;
  void addFace(const Face& face);
  void setErrorString(const QString& errorMessage);
  void proccessingSuccesful();
  void proccessingFailed();
  void setPictureName(const QString& name);
private:
  std::shared_ptr<QVector<Face>> mFaces;
  QString mPictureName;
  bool mIsProcessed;
  QString mErrorString;
};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_PICTURE_HPP
