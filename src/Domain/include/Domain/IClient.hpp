#ifndef TEVIANCLIENT_DOMAIN_ICLIENT_HPP
#define TEVIANCLIENT_DOMAIN_ICLIENT_HPP

#include <QNetworkRequest>
#include <QByteArray>
#include <QObject>
#include <QString>

namespace Domain {

class IClient : public QObject
{
    Q_OBJECT
public:
  virtual ~IClient() = default;

  /*!
   * \brief getJWToken Получить JWToken
   * \return JWToken токен
   */
  virtual QString getJWToken() const = 0;

  /*!
   * \brief postRequest Отправить POST запрос
   * \param request запрос
   * \param data тело запроса
   */
  virtual void postRequest(QNetworkRequest& request, QByteArray& data) = 0;

private:
  /*!
   * \brief authentication Аутентификация
   */
  virtual void authentication() = 0;

  /*!
   * \brief setJWToken Установить JWToken
   * \param token токен
   */
  virtual void setJWToken(const QString& token) = 0;

  /*!
   * \brief handler Обработчик запроса
   * \param path путь
   * \param data тело ответа
   */
  virtual void handler(const QString& path, const QByteArray& data) = 0;

};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_ICLIENT_HPP
