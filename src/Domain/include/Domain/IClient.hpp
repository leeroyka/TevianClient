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

private:
    virtual void authentication() = 0;
    virtual void setJWToken(const QString& token) = 0;
    virtual QString getJWToken() const = 0;
    virtual void postRequest(QNetworkRequest& request, QByteArray& data) = 0;
    virtual void handler(const QString& path, const QByteArray& data) = 0;

};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_ICLIENT_HPP
