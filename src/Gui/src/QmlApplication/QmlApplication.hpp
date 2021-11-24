#ifndef TEVIANCLIENT_GUI_QML_APPLICATION_HPP
#define TEVIANCLIENT_GUI_QML_APPLICATION_HPP

#include <QVariant>
#include <QString>
#include <QFile>
#include <QSettings>
#include <QObject>

#include <Domain/TevianClient.hpp>

namespace Gui {

class QmlApplication: public QObject

{
  Q_OBJECT
public:
  QmlApplication(QObject * parent = nullptr);
  ~QmlApplication();

signals:


public slots:

  void getHttpPost();

  void testFunc();
private:

  std::shared_ptr<Domain::TevianClient> mTClient;

};
} // namespace Gui

#endif// TEVIANCLIENT_GUI_QML_APPLICATION_HPP
