#ifndef TEVIANCLIENT_GUI_QML_APPLICATION_HPP
#define TEVIANCLIENT_GUI_QML_APPLICATION_HPP

#include <QVariant>
#include <QString>
#include <QFile>
#include <QSettings>
#include <QObject>
#include <QList>

#include <Domain/TevianClient.hpp>

namespace Gui {

class QmlApplication: public QObject

{
  Q_OBJECT
public:
  QmlApplication(QObject * parent = nullptr);
  ~QmlApplication();

signals:
  void errorRecived(const QString& error);
  void imagesProcessed();
  void imagesReady(const QVariantList& images);
  void imageProcessed(const qint32 images, const qint32 maxImages);

public slots:
  void initialization();
  void uploadImages(const QList<QUrl>& pathsImages);
  void processedImages(std::shared_ptr<QVector<Domain::Picture>> pictures);
  void getImage(const QString& path) const;

private:
  std::shared_ptr<Domain::TevianClient> mTClient;

};
} // namespace Gui

#endif// TEVIANCLIENT_GUI_QML_APPLICATION_HPP
