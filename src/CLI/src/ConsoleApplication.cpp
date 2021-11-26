#include <ConsoleApplication.hpp>

#include <QJsonDocument>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>
#include <QUrl>

#include <iostream>

CLI::ConsoleApplication::ConsoleApplication()
{
  mTClient = std::make_shared<Domain::TevianClient>();
  connect(mTClient.get(), &Domain::TevianClient::onUpdatePictures,
          this, &ConsoleApplication::picturesRecived);
}

void CLI::ConsoleApplication::uploadImages(const QVector<QString>& pathImages) const
{
  try
  {
    mTClient->addImages(pathImages);
  }
  catch (const std::exception& error)
  {
    qCritical()<< error.what()<<'\n';
  }
  catch (...)
  {
    qCritical()<<"Unknown error"<<'\n';
  }
}

void CLI::ConsoleApplication::uploadFolder(const QString& pathFolder) const
{
  QDir dir;
  dir.setPath(pathFolder);
  QVector<QString> pathImages;
  for(auto& path : dir.entryList({"*.jpeg","*.jpg", "*.png"},QDir::Files | QDir::Readable,QDir::NoSort))
  {
    #if defined(Q_OS_WIN)
      pathImages.push_back(pathFolder+'\\'+path);
      continue;
    #endif
    pathImages.push_back(pathFolder+'/'+path);
  }
  if(pathImages.empty())
    return;
  uploadImages(pathImages);
}

void CLI::ConsoleApplication::picturesRecived(std::shared_ptr<QVector<Domain::Picture> > pictures)
{
  QTextStream(stdout) <<"Image processed: "<< pictures->back().getPictureName()<<'\n';
  if(pictures->size() == mTClient->getNumberOfImages())
  {
    QJsonArray jsonPicturesArray;
    for(auto& picture : *pictures)
    {
      QJsonObject jsonPicture;
      jsonPicture["path"] = picture.getPictureName();
      QJsonArray jsonFacesArray;
      for(auto& face : *picture.getFaces())
      {
        QJsonObject jsonFace;
        jsonFace["x"] =      face.getX();
        jsonFace["y"] =      face.getY();
        jsonFace["width"] =  face.getWidth();
        jsonFace["height"] = face.getHeight();
        jsonFace["Age"] =    face.getAge();
        jsonFace["Gender"] = face.getGender();
        jsonFacesArray.append(jsonFace);
      }
      jsonPicture["faces"] = jsonFacesArray;
      jsonPicturesArray.append(jsonPicture);
    }
    QJsonObject json;
    json["pictures"] = jsonPicturesArray;
    QJsonDocument jsonDoc(json);
    QString jsonString = jsonDoc.toJson();
    QTextStream(stdout) << jsonString;
  }
}
