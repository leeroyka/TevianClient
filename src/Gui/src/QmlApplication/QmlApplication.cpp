#include <QmlApplication/QmlApplication.hpp>

namespace Gui
{

QmlApplication::QmlApplication(QObject *parent) : QObject(parent)
{

}

QmlApplication::~QmlApplication()
{

}

void QmlApplication::initialization()
{
  try
  {
    qDebug()<<"initialization";
    mTClient = std::make_shared<Domain::TevianClient>();
  }
  catch (const std::exception& error)
  {
    emit errorRecived(error.what());
  }
  catch (...)
  {
    emit errorRecived("Unknown error");
  }
  connect(mTClient.get(), &Domain::TevianClient::onUpdatePictures, this, &QmlApplication::processedImages);
}

void QmlApplication::uploadImages(const QList<QUrl>& pathsImages)
{
  emit imagesProcessed();
  QVector<QString> images;
  try
  {
    for(auto path : pathsImages)
    {
      images.push_back(path.toString().remove(0,QString("file:///").length()));
    }
    mTClient->addImages(images);
  }
  catch (const std::exception& error)
  {
    emit errorRecived(error.what());
  }
  catch (...)
  {
    emit errorRecived("Unknown error");
  }
}

void QmlApplication::processedImages(std::shared_ptr<QVector<Domain::Picture>> pictures)
{
  emit imageProcessed(pictures->size(), mTClient->getNumberOfImages());
  if(pictures->size() == mTClient->getNumberOfImages())
  {
        QVariantList images;
        for(auto picture : *pictures)
        {
            images.push_back(picture.getPictureName());
        }
        emit imagesReady(images);
  }
}


} // namespace Gui

