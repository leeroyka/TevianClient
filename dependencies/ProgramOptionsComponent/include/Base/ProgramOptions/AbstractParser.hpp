#ifndef BASE_PROGRAM_OPTIONS_PARSER_HPP
#define BASE_PROGRAM_OPTIONS_PARSER_HPP

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace ProgramOptions {

//! Класс для работы с аргументами командной строки
class AbstractParser
{
public:
  virtual ~AbstractParser() = default;

public:
  /*!
   * \brief Добавляет новую опцию командной строки
   * \details Если указан формат аргумента, то аргумент обязателен
   * \param name - длинное название опции
   * \param abbreviation - короткое название опции
   * \param description - описание опции для автогенерируемой инструкции
   * \param argumentFormat - формат аргумента (например, "path")
   */
  void addOption(const std::string& name,
                 const char&        abbreviation   = 0,
                 const std::string& description    = "",
                       std::string  argumentFormat = "");

  /*!
   * \brief Разбирает аргументы
   * \details Разбирает аргументы mArgc и mArgv, передаваемые в конструкторе
   * \return bool - true если можно продолжать выполнение программы, иначе false
   */
  bool parse();

  /*!
   * \brief Определяет, указан ли при запуске программы аргумент командной строки с данным названием
   * \param option - аргумент командной строки
   * \return bool - если такой аргумент присутствует - true, иначе false
   */
  bool has(const std::string& option) const;

  /*!
   * \brief Возвращает значение аргумента командной строки
   * \param option - опция командной строки
   * \return std::string - значения аргумента опции
   * \throw Exceptions, если опция не существует или не указан параметр
   */
  std::string operator[](const std::string& option) const;

  /*!
   * \brief Возвращает имя программы
   * \return std::string - имя программы
   */
  const std::string getProgramName() const;

protected:
  /*!
   * \brief Конструктор класса
   * \details Автоматически добавляет опции help и version
   * --help, -h, --version, -v
   * \param argc - количество аргументов командной строки
   * \param argv - аргументы командной строки
   */
  AbstractParser(const int& argc, const char** argv);

private:
  //! Отображение автогенерируемой инструкции в консоли
  void printUsage() const;

  //! Отображение верии программы
  void printVersion() const;

private: // PURE VIRTUAL
  virtual size_t getMajorVersion() const = 0;
  virtual size_t getMinorVersion() const = 0;

protected:
  po::options_description mDescription{"Options"}; //!< Перечисление опций командной строки
  po::variables_map mParsedArgs;                   //!< Обработанные аргументы

  std::map<std::string, std::string> mUsage; //!< Строки автогенерируемой инструкции

private:
  std::string mProgramName; //!< Имя программы

  const int    mArgc; //!< Количество аргументов командной строки
  const char** mArgv; //!< Аргументы командной строки

};

} // namespace ProgramOptions

#endif // BASE_PROGRAM_OPTIONS_PARSER_HPP
