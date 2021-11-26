#ifndef TEVIANCLIENT_CLI_CONSOLEAPPLICATION_HPP
#define TEVIANCLIENT_CLI_CONSOLEAPPLICATION_HPP

#include <Domain/TevianClient.hpp>

namespace CLI {

class ConsoleApplication : public QObject
{
  Q_OBJECT

public:
  /*!
   * \brief ConsoleApplication Конструктор по умолчанию для консольного клиента
   */
  ConsoleApplication();

public slots:
  /*!
   * \brief uploadImages загрузка изображений
   * \param pathImages путь до изображений
   */
  void uploadImages(const QVector<QString>& pathImages) const;

  /*!
   * \brief uploadFolder загрузка изображений из папки
   * \param pathFolder путь до папки
   */
  void uploadFolder(const QString& pathFolder) const;

  /*!
   * \brief picturesRecived обработка полученных изображений
   * \param pictures указатель на вектор изображений
   */
  void picturesRecived(std::shared_ptr<QVector<Domain::Picture>> pictures);

private:
  std::shared_ptr<Domain::TevianClient> mTClient; ///< Клиент
};

} // namespace CLI

#endif// TEVIANCLIENT_CLI_CONSOLEAPPLICATION_HPP
