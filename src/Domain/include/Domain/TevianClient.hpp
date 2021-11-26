#ifndef TEVIANCLIENT_DOMAIN_TEVIANCLIENT_HPP
#define TEVIANCLIENT_DOMAIN_TEVIANCLIENT_HPP

#include <Domain/IClient.hpp>
#include <Domain/Picture.hpp>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <memory>

namespace Domain {

class TevianClient : public IClient
{
    Q_OBJECT
public:
  /*!
     * \brief TevianClient конструктор по умолчанию для клиента
     */
  TevianClient();

signals:
  /*!
   * \brief onUpdatePictures сигнал о получении изображений
   */
  void onUpdatePictures(std::shared_ptr<QVector<Picture>>);

public slots:
  /*!
   * \brief addImages добавить изображение
   * \param images изображение
   * \return количество изображений
   */
  qint32 addImages(const QVector<QString>& images);

  /*!
   * \brief getNumberOfImages получить количество изображений
   * \return количество изображений
   */
  size_t getNumberOfImages() const;

  /*!
   * \brief getPictures получить указатель на вектор изображений
   * \return указатель на вектор изображений
   */
  std::shared_ptr<QVector<Picture>> getPictures() const;

  /*!
   * \brief getPicturesSize Получить количество обработанных изображений
   * \return количество обработанных изображений
   */
  size_t getPicturesSize() const;

  /*!
   * \brief getJWToken получить JWToken токен
   * \return токен
   */
  QString getJWToken() const override;

  /*!
   * \brief postRequest Отправка POST запроса
   * \param request Запрос
   * \param data Тело запроса
   */
  void postRequest(QNetworkRequest& request, QByteArray& data) override;

private:
  /*!
   * \brief authentication аутентификация
   */
  void authentication() override;

  /*!
   * \brief setJWToken установить JWToken токен
   * \param token токен
   */
  void setJWToken(const QString& token) override;

  /*!
   * \brief detectRequest поиск лиц на изображении
   * \param imagePath путь до изображения
   */
  void detectRequest(const QString& imagePath);

  /*!
   * \brief handler Обработчик ответа от сервера
   * \param path путь
   * \param data тело ответа
   */
  void handler(const QString& path, const QByteArray& data) override;

private:
  std::shared_ptr<QVector<Picture>> mPictures; ///< указатель на вектор изображений

  size_t  mNumberOfImages; ///< Количество изображений
  QString mJWToken;        ///< JWToken Токен

  const QString M_LOGIN    = "blokhin321@gmail.com"; ///< логин для аутентификации
  const QString M_PASSWORD = "8765432l";             ///< пароль для аутентификации

  const QString M_SERVER      = "https://backend.facecloud.tevian.ru/"; ///< хост
  const QString M_PATH_LOGIN  = "/api/v1/login";                        ///< путь до аутентификации
  const QString M_PATH_DETECT = "/api/v1/detect";                       ///< путь до обработчика изображения

  const QString M_CONTENT_TYPE_JSON = "application/json"; ///< Content-type для json запросов
  const QString M_CONTENT_TYPE_JPEG = "image/jpeg";       ///< Content-type для запросов в виде изображений
};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_TEVIANCLIENT_HPP
