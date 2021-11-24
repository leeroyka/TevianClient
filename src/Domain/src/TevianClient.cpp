#include <Domain/TevianClient.hpp>

#include <QFile>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QUrlQuery>
#include <QEventLoop>
#include <QJsonArray>

#include <stdexcept>

//  auto responsePOST = client.post(Base::Interfaces::IHttpClient::HttpRequest({
//                        {{"Authorization", "Bearer "+token},{"Content-type","image/jpeg"}},
//                        "https://backend.facecloud.tevian.ru/api/v1/detect",
//                        {},
//                        b64Enc}));
//  auto a = responsePOST.data;

//eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpYXQiOjE2Mzc2NTU4NTMsIm5iZiI6MTYzNzY1NTg1MywianRpIjoiY2EyMmIyYzEtZmE1OC00OWRkLTljMGEtMWYwNDlkYWI4ZjEyIiwic3ViIjoyNzIsImZyZXNoIjpmYWxzZSwidHlwZSI6ImFjY2VzcyJ9.o4uKVenHwmahLprqwYPWdt76Sg9RcbSRdGgswnY4T2s


Domain::TevianClient::TevianClient(QObject* parent)
  : QObject(parent)
  , mNumberOfImages(0)
{
  mPictures = std::make_shared<QVector<Picture>>();
  authentication();
}

qint32 Domain::TevianClient::addImages(const QVector<QString>& images)
{
  mNumberOfImages += images.size();
  for(auto path : images)
  {
    detectRequest(path);
  }
  return mNumberOfImages;
}

size_t Domain::TevianClient::getNumberOfImages() const
{
  return mNumberOfImages;
}

std::shared_ptr<QVector<Domain::Picture> > Domain::TevianClient::getPictures() const
{
  return mPictures;
}

size_t Domain::TevianClient::getPicturesSize() const
{
  return mPictures->size();
}

void Domain::TevianClient::authentication()
{
  QEventLoop loop;
  QUrl url(M_SERVER);
  url.setPath(M_PATH_LOGIN);

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, M_CONTENT_TYPE_JSON);

  QJsonObject jsonBody;
  jsonBody["email"]    = M_LOGIN;
  jsonBody["password"] = M_PASSWORD;

  QByteArray rawData = QJsonDocument(jsonBody).toJson();

  std::unique_ptr<QNetworkAccessManager> mNetworkManager = std::make_unique<QNetworkAccessManager>();
  QNetworkReply* reply = mNetworkManager->post(request, rawData);
  connect(mNetworkManager.get(), &QNetworkAccessManager::finished, [=]()
  {
    if (reply->error())
        throw std::runtime_error("Authentication error: " +reply->errorString().toStdString());

    QByteArray rawData(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(rawData);
    QJsonObject jsonData = json["data"].toObject();
    setJWToken(jsonData["access_token"].toString());
    qDebug()<<getJWToken();
  });
  reply->ignoreSslErrors();
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();
}

void Domain::TevianClient::setJWToken(const QString& token)
{
  mJWToken = "Bearer "+token;
}

void Domain::TevianClient::detectRequest(const QString& imagePath)
{
  QEventLoop loop;
  QUrl url(M_SERVER);
  url.setPath(M_PATH_DETECT);

  QUrlQuery query;
  query.addQueryItem("demographics","true");
  url.setQuery(query);

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, M_CONTENT_TYPE_JPEG);
  request.setRawHeader("Authorization", getJWToken().toUtf8());

  QFile image(imagePath);
  if(!image.open(QIODevice::ReadOnly))
    throw std::runtime_error("Failed image opening");

  QByteArray rawImage(image.readAll());

    std::unique_ptr<QNetworkAccessManager> mNetworkManager = std::make_unique<QNetworkAccessManager>();
  QNetworkReply* reply = mNetworkManager->post(request, rawImage);
  connect(mNetworkManager.get(), &QNetworkAccessManager::finished, [=]()
  {
    Picture picture;
    picture.setPictureName(imagePath);
    qDebug()<<imagePath;
    if (reply->error())
    {
      picture.proccessingFailed();
      picture.setErrorString(reply->errorString());
      mPictures->push_back(picture);
      return ;
    }
    picture.proccessingSuccesful();

    QByteArray rawData(reply->readAll());
    QJsonDocument jsonReply(QJsonDocument::fromJson(rawData));

    for(auto jsonValue : jsonReply["data"].toArray())
    {
      auto valueObject = jsonValue.toObject();

      auto rectangleObject = valueObject["bbox"].toObject();

      Face face(rectangleObject["x"].toInt(),
                rectangleObject["y"].toInt(),
                rectangleObject["height"].toInt(),
                rectangleObject["width"].toInt());

      auto demographicObject = valueObject["demographics"].toObject();
      face.setAge(demographicObject["age"].toObject()["mean"].toDouble(),
                  demographicObject["age"].toObject()["variance"].toDouble());
      face.setGender(demographicObject["gender"].toString());
      picture.addFace(face);
    }
    mPictures->push_back(picture);
  });
  reply->ignoreSslErrors();
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();
}

QString Domain::TevianClient::getJWToken() const
{
  return mJWToken;
}

//TODO
/*
void Domain::TevianClient::postRequest(QNetworkRequest& request, QByteArray& data)
{
  QEventLoop loop;
  QNetworkReply* reply = mNetworkManager->post(request, data);
  connect(mNetworkManager.get(), &QNetworkAccessManager::finished, [=]()
  {

    if (reply->error())

      throw std::runtime_error("REST Api Error: " +reply->errorString().toStdString());
    QByteArray rawData(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(rawData);
    QJsonObject metaData;
    metaData["path"] = request.url().path();

  });
  reply->ignoreSslErrors();
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();
}*/
