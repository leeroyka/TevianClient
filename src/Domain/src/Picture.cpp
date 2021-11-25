#include <Domain/Picture.hpp>


Domain::Picture::Picture()
{
    mFaces = std::make_shared<QVector<Face>>();
}

QString Domain::Picture::getPictureName() const
{
    return mPictureName;
}

void Domain::Picture::addFace(const Domain::Face& face)
{
  mFaces->push_back(face);
}

void Domain::Picture::setErrorString(const QString& errorMessage)
{
  mErrorString = errorMessage;
}

void Domain::Picture::proccessingSuccesful()
{
  mIsProcessed = true;
}

void Domain::Picture::proccessingFailed()
{
  mIsProcessed = false;
}

void Domain::Picture::setPictureName(const QString& name)
{
  mPictureName = name;
}
