#include <Domain/TevianClient.hpp>

#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QJsonArray>
#include <QUrlQuery>
#include <QFile>
#include <QUrl>

#include <stdexcept>

//eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpYXQiOjE2Mzc2NTU4NTMsIm5iZiI6MTYzNzY1NTg1MywianRpIjoiY2EyMmIyYzEtZmE1OC00OWRkLTljMGEtMWYwNDlkYWI4ZjEyIiwic3ViIjoyNzIsImZyZXNoIjpmYWxzZSwidHlwZSI6ImFjY2VzcyJ9.o4uKVenHwmahLprqwYPWdt76Sg9RcbSRdGgswnY4T2s

Domain::TevianClient::TevianClient()
  :  mNumberOfImages(0)
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
  QUrl url(M_SERVER);
  url.setPath(M_PATH_LOGIN);

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, M_CONTENT_TYPE_JSON);

  QJsonObject jsonBody;
  jsonBody["email"]    = M_LOGIN;
  jsonBody["password"] = M_PASSWORD;

  QByteArray rawData = QJsonDocument(jsonBody).toJson();

  postRequest(request, rawData);
}

void Domain::TevianClient::setJWToken(const QString& token)
{
  mJWToken = "Bearer "+token;
}

void Domain::TevianClient::detectRequest(const QString& imagePath)
{
  QUrl url(M_SERVER);
  url.setPath(M_PATH_DETECT);

  QUrlQuery query;
  query.addQueryItem("demographics","true");
  url.setQuery(query);

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, M_CONTENT_TYPE_JPEG);
  request.setRawHeader("Authorization", getJWToken().toUtf8());
  request.setRawHeader("Content-Disposition", imagePath.toUtf8());

  QFile image(imagePath);
  if(!image.open(QIODevice::ReadOnly))
    throw std::runtime_error("Failed image opening");

  QByteArray rawImage(image.readAll());
    postRequest(request,rawImage);
}

QString Domain::TevianClient::getJWToken() const
{
  return mJWToken;
}

//TODO

void Domain::TevianClient::postRequest(QNetworkRequest& request, QByteArray& data)
{
  QEventLoop loop;
  std::unique_ptr<QNetworkAccessManager>
          mNetworkManager = std::make_unique<QNetworkAccessManager>();
  QNetworkReply* reply = mNetworkManager->post(request, data);
  connect(mNetworkManager.get(), &QNetworkAccessManager::finished, [=]()
  {

    QJsonObject json;
    if (reply->error())
    {
        json["error"] = reply->errorString();
    }
    else
    {
        QByteArray rawData(reply->readAll());
        json = QJsonDocument::fromJson(rawData).object();
    }
    if(request.hasRawHeader("Content-Disposition"))
        json["Content-Disposition"] = QString(request.rawHeader("Content-Disposition"));
    handler(request.url().path(),QJsonDocument(json).toJson());

  });
  reply->ignoreSslErrors();
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();
}

void Domain::TevianClient::handler(const QString& path, const QByteArray& data)
{
    if(path == M_PATH_LOGIN)
    {
        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.object().contains("error"))
        {
            throw std::runtime_error("Authorization error: " +
                                     json.object()["error"].toString().toStdString());
        }
        QJsonObject jsonData = json["data"].toObject();
        setJWToken(jsonData["access_token"].toString());
    } else if(path == M_PATH_DETECT)
    {
        Picture picture;
        QJsonDocument json = QJsonDocument::fromJson(data);
        picture.setPictureName(json.object()["Content-Disposition"].toString());
        if (json.object().contains("error"))
        {
          picture.proccessingFailed();
          picture.setErrorString(json.object()["error"].toString());
          mPictures->push_back(picture);
          return ;
        }
        picture.proccessingSuccesful();

        for(auto jsonValue : json["data"].toArray())
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
        emit onUpdatePictures(mPictures);
    }
}
