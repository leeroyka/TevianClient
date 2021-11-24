#ifndef HTTP_HTTPCLIENT_SPEAKER_HPP
#define HTTP_HTTPCLIENT_SPEAKER_HPP

#include <Http/HttpClient/Interfaces/IHTTPSpeaker.hpp>

#include <curl/curl.h>

#include <memory>

namespace Base {
namespace HttpClient {

class Client : public Interfaces::IHttpClient::ISpeaker
{
public:
  /*!
     * \brief Конструктор клиента. Null-object
     * \throw std::runtime_error Ошибка инициализации Curl
     */
  Client();

  Interfaces::IHttpClient::HttpResponse post(Interfaces::IHttpClient::HttpRequest req) override final;

  Interfaces::IHttpClient::HttpResponse put(Interfaces::IHttpClient::HttpRequest req) override final;

  Interfaces::IHttpClient::HttpResponse get(Interfaces::IHttpClient::HttpRequest req) override final;

private:
  /*!
     * \brief Посылает HTTP запрос
     * \param method Название метода
     * \param HttpRequest сформированный запрос
     * \return HttpResponse Возвращает сформированный ответ
     * \throw std::runtime_error Ошибка запроса Curl
     */
  Interfaces::IHttpClient::HttpResponse request(const std::string& method, Interfaces::IHttpClient::HttpRequest req) override;

private:
  std::shared_ptr<CURL> mCurl;
};

} // namespace HttpClient
} // namespace Base

#endif // HTTP_HTTPCLIENT_SPEAKER_HPP
