#ifndef TEVIANCLIENT_DOMAIN_TEVIANCLIENT_HPP
#define TEVIANCLIENT_DOMAIN_TEVIANCLIENT_HPP

#include <Domain/Picture.hpp>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <memory>

namespace Domain {

class TevianClient : public QObject
{
    Q_OBJECT
public:
    TevianClient(QObject* parent = nullptr);


public slots:
    qint32 addImages(const QVector<QString>& images);
    size_t getNumberOfImages() const;
    std::shared_ptr<QVector<Picture>> getPictures() const;
    size_t getPicturesSize() const;
    // TODO DOXYGEN DOCUMENTATION
private:
    void authentication();
    void setJWToken(const QString& token);
    void detectRequest(const QString& imagePath);
    QString getJWToken() const;
    void postRequest(QNetworkRequest& request, QByteArray& data);

private:
    std::shared_ptr<QVector<Picture>> mPictures;

    size_t mNumberOfImages;
    QString mJWToken;

    const QString M_LOGIN    = "blokhin321@gmail.com";
    const QString M_PASSWORD = "8765432l";

    const QString M_SERVER      = "https://backend.facecloud.tevian.ru/";
    const QString M_PATH_LOGIN  = "/api/v1/login";
    const QString M_PATH_DETECT = "/api/v1/detect";

    const QString M_CONTENT_TYPE_JSON = "application/json";
    const QString M_CONTENT_TYPE_JPEG = "image/jpeg";
};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_TEVIANCLIENT_HPP
