#ifndef HTTP_HTTPCLIENT_CALLBACK_HPP
#define HTTP_HTTPCLIENT_CALLBACK_HPP

#include <ostream>
#include <istream>

namespace Base {
namespace HttpClient {

/*!
 * \brief Набор сценариев для чтения и записи cURL
 */
class Callback
{
public:
  /*!
   * \brief Функция записи данных из удаленного хранилища в поток
   * \param buffer Данные на сервере
   * \param block Размер одного передаваемого блока
   * \param nmemb Кол-во передаваемых блоков
   * \param stream Поток для записи
   * \return size_t Размер записанных данных
   * \throw std::exception Ошибка удаленного хранилища
   */
  static size_t write(char* buffer, size_t block, size_t nmemb, std::ostream* stream);

  /*!
   * \brief Функция записи данных на удаленное хранилище из потока
   * \param data Данные на сервере
   * \param block Размер одного передаваемого блока
   * \param nmemb Кол-во передаваемых блоков
   * \param stream Поток для чтения
   * \return size_t Размер прочитанных данных
   * \throw std::exception Ошибка удаленного хранилища
   */
  static size_t read(char* data, size_t block, size_t nmemb, std::istream* stream);

};

} // namespace HttpClient
} // namespace Base

#endif // HTTP_HTTPCLIENT_CALLBACK_HPP
