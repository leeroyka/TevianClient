#ifndef HTTP_HTTPCLIENT_IHTTP_SPEAKER_HPP
#define HTTP_HTTPCLIENT_IHTTP_SPEAKER_HPP

#include <string>
#include <map>

namespace Base {
namespace Interfaces {
namespace IHttpClient {

struct HttpRequest
{
  std::map<std::string, std::string> headers; ///< Заголовоки HTTP-запроса
  std::string url;                            ///< URL адресс HTTP-запроса
  std::map<std::string, std::string> uriArgs; ///< GET-параметры HTTP-запроса
  std::string body;                           ///< контент HTTP-запроса
};

struct HttpResponse
{
  size_t        status;      ///< код статуса HTTP-ответа
  std::string   contentType; ///< тип контента HTTP-запроса
  std::string   data;        ///< контент HTTP-запроса
};

class ISpeaker
{
public:
  virtual ~ISpeaker() = default;

  /*!
   * \brief Посылает POST запрос
   * \param HttpRequest сформированный запрос
   * \return HttpResponse Возвращает сформированный ответ
   */
  virtual HttpResponse post(HttpRequest req) = 0;

  /*!
   * \brief Посылает PUT запрос
   * \param HttpRequest сформированный запрос
   * \return HttpResponse Возвращает сформированный ответ
   */
  virtual HttpResponse put(HttpRequest req) = 0;

  /*!
   * \brief Посылает GET запрос
   * \param HttpRequest сформированный запрос
   * \return HttpResponse Возвращает сформированный ответ
   */
  virtual HttpResponse get(HttpRequest req) = 0;

private:
  virtual HttpResponse request(const std::string& method, IHttpClient::HttpRequest req) = 0;

};

} // namespace IHttpClient
} // namespace Interfaces
} // namespace Base

#endif // HTTP_HTTPCLIENT_IHTTP_SPEAKER_HPP
