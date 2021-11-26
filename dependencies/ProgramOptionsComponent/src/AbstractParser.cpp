#include <Base/ProgramOptions/AbstractParser.hpp>

#include <iostream>
#include <iomanip>

namespace ProgramOptions {


void AbstractParser::addOption(const std::string& name,
                       const char&        abbreviation,
                       const std::string& description,
                             std::string  argumentFormat)
{
  // Составляем строку фомата "длиннаяОпция,короткаяОпция", если есть короткий вариант опции
  std::string extendedOption = name;
  std::string shortOptDescription = "  ";
  if(abbreviation)
  {
    extendedOption += std::string(",") + abbreviation;
    shortOptDescription = std::string("-") + abbreviation;
  }

  // Добавляем в описание опций
  if(!argumentFormat.empty())
  {
    mDescription.add_options()
      (extendedOption.data(), po::value<std::string>()->default_value(""), description.data());
    argumentFormat = std::string(" <") + argumentFormat + std::string(">");
  }
  else
    mDescription.add_options()
      (extendedOption.data(), description.data());

  // Для верного форматирования создаем две строки:
  // левая часть содержит в себе длинную опцию и параметр,
  // правая - короткую опцию и описание
  mUsage.insert({"--" + name + argumentFormat, shortOptDescription + "\t\t" + description});
}

bool AbstractParser::parse()
{
  if(!mArgc)
    return false;

  try
  {
    po::store(po::parse_command_line(mArgc, mArgv, mDescription), mParsedArgs);
  }
  catch(std::exception)
  {
    printUsage();
    return false;
  }

  if(has("help"))
  {
    printUsage();
    return false;
  }
  if(has("version"))
  {
    printVersion();
    return false;
  }

  return true;
}

bool AbstractParser::has(const std::string& option) const
{
  if(mParsedArgs.empty())
    return false;

  return mParsedArgs.count(option);
}

std::string AbstractParser::operator[](const std::string &option) const
{
  if(mParsedArgs.empty())
    throw std::runtime_error("NOT PARSED ERROR");

  try
  {
    return mParsedArgs[option].as<std::string>();
  }
  catch(std::exception)
  {
    throw std::runtime_error("FIND ERROR");
  }
}

const std::string AbstractParser::getProgramName() const
{
  return mProgramName;
}

AbstractParser::AbstractParser(const int& argc, const char** argv)
  : mProgramName("unknown")
  , mArgc(argc)
  , mArgv(argv)
{
  addOption("help", 'h', "Show Help Screen");
  addOption("version", 'v', "Show Version");

  if(!mArgv)
    return;
    
  std::string programPath = mArgv[0];
  mProgramName = programPath.substr(programPath.rfind('/') + 1); // +1, чтобы убрать / из имени программы
}

void AbstractParser::printUsage() const
{
  // Имя программы
  std::cout << "Usage " << getProgramName()<< "\nOptions:" << "\n";

  size_t maxLength = 0;
  for(const auto& usagePair : mUsage)
    if(usagePair.first.length() > maxLength)
      maxLength = usagePair.first.length();

  // Выводим, форматируя
  for(const auto& usagePair : mUsage)
    std::cout << std::setiosflags(std::ios::left)
              << std::setw(static_cast<int>(maxLength) + 4) // 4 пробела выглядят довольно неплохо
              << usagePair.first << usagePair.second << "\n";
  std::cout << "\n";
}

void AbstractParser::printVersion() const
{
  std::cout << getMajorVersion() << '.' << getMinorVersion() << '\n';
}

} // namespace ProgramOptions
