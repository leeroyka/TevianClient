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
  mTClient = std::make_shared<Domain::TevianClient>();
  qDebug()<<mTClient->addImages({"D:\\test.jpg","D:\\test2.jpg"});
  qDebug()<<mTClient->addImages({"D:\\test3.jpg"});
}

void QmlApplication::testFunc()
{
    auto pictures = *mTClient->getPictures();
}


} // namespace Gui

