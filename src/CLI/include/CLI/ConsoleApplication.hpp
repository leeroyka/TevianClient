#ifndef TEVIANCLIENT_CLI_CONSOLEAPPLICATION_HPP
#define TEVIANCLIENT_CLI_CONSOLEAPPLICATION_HPP

#include <Domain/TevianClient.hpp>

namespace CLI {

class ConsoleApplication : public QObject
{
  Q_OBJECT

public:
  ConsoleApplication();

public slots:
  void uploadImages(const QVector<QString>& pathImages) const;
  void uploadFolder(const QString& pathFolder) const;
  void picturesRecived(std::shared_ptr<QVector<Domain::Picture>> pictures);
private:
  std::shared_ptr<Domain::TevianClient> mTClient;
};

} // namespace CLI

#endif// TEVIANCLIENT_CLI_CONSOLEAPPLICATION_HPP
