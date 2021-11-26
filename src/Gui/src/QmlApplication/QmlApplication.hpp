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
  /*!
   * \brief errorRecived сигнал получения ошибки
   * \param error ошибка
   */
  void errorRecived(const QString& error);

  /*!
   * \brief imagesProcessed сигнал о начале обработки изображений
   */
  void imagesProcessed();

  /*!
   * \brief imagesReady сигнал об окончании обработки изображений
   * \param images вектор изображений
   */
  void imagesReady(const QVariantList& images);

  /*!
   * \brief imageProcessed  сигнал о получении обработанного изображения
   * \param images количество обработанных изображений
   * \param maxImages всего изображений
   */
  void imageProcessed(const qint32 images, const qint32 maxImages);

  /*!
   * \brief facesRecived сигнал о получении данных лиц
   * \param faces лица
   */
  void facesRecived(const QVariantList& faces);

public slots:
  /*!
   * \brief initialization инициализация клиента
   */
  void initialization();

  /*!
   * \brief uploadImages загрузка изображений
   * \param pathsImages путь до изображений
   */
  void uploadImages(const QList<QUrl>& pathsImages);

  /*!
   * \brief uploadFolder Загрузка изображений из папки
   * \param pathFolder путь до папки
   */
  void uploadFolder(const QUrl& pathFolder);

  /*!
   * \brief processedImages Обработка обработанных изображений
   * \param pictures Обработанные изображения
   */
  void processedImages(std::shared_ptr<QVector<Domain::Picture>> pictures);

  /*!
   * \brief getImage получение изображения
   * \param path путь до изображения
   */
  void getImage(const QString& path);


private:
  std::shared_ptr<Domain::TevianClient> mTClient; ///< Клиент

};
} // namespace Gui

#endif// TEVIANCLIENT_GUI_QML_APPLICATION_HPP
