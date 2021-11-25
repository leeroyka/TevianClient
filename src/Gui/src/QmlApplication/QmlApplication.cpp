#include <QmlApplication/QmlApplication.hpp>

namespace Gui
{

QmlApplication::QmlApplication(QObject *parent) : QObject(parent)
{

}

QmlApplication::~QmlApplication()
{

}
// TODO TRY CATCH Обработка
void QmlApplication::getHttpPost()
{
  int adsdas;
  qDebug()<<mTClient->addImages({"/home/blokhin/Documents/test.jpeg"});
  qDebug()<<mTClient->addImages({"/home/blokhin/Documents/test2.jpg"});
}

void QmlApplication::testFunc()
{
  auto pictures = *mTClient->getPictures();
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
  for(auto path : pathsImages)
  {
    images.push_back(path.toString().remove(0,QString("file:///").length()));
  }
  mTClient->addImages(images);
}

void QmlApplication::processedImages(std::shared_ptr<QVector<Domain::Picture>> pictures)
{
  emit imageProcessed(pictures->size(), mTClient->getNumberOfImages());
}


} // namespace Gui

