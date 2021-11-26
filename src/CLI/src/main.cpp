#include <ConsoleApplication.hpp>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QCommandLineParser parser;
  parser.setApplicationDescription("TevianClient CLI");
  parser.addHelpOption();

  QCommandLineOption path_option(QStringList() << "pathDir", "path to directory", "pathDir");
  parser.addOption(path_option);

  QCommandLineOption images_option(QStringList() << "images", "paths to images", "images");
  parser.addOption(images_option);

  parser.process(a);

  try {
    std::shared_ptr<CLI::ConsoleApplication> application;
    application = std::make_shared<CLI::ConsoleApplication>();
    if(parser.isSet(images_option))
    {
      auto pathList = parser.value("images").split(';');
      QVector<QString> pathVector;
      for(auto& path : pathList)
        pathVector.push_back(path);
      application->uploadImages(pathVector);
    }
    if(parser.isSet(path_option))
    {
      application->uploadFolder(parser.value("pathDir"));
    }
  }
  catch (const std::exception& error)
  {
    QTextStream(stdout)<<"Authorization error: "<<error.what()<<'\n';
  }
  catch(...)
  {
    QTextStream(stdout)<<"Unknown error";
  }

  return a.exec();
}
