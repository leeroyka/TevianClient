#ifndef BASE_PROGRAM_OPTIONS_SINGLETON_PARSER_HPP
#define BASE_PROGRAM_OPTIONS_SINGLETON_PARSER_HPP

#include <Base/ProgramOptions/AbstractParser.hpp>

namespace ProgramOptions {

/*!
 * \brief Синглтон-реализация парсера аргументов командной строки
 */
class SingletonParser : public AbstractParser
{
public:
  /*!
   * \brief Возвращает единственный объект парсера.
   * \details Если вызывается первый раз, то инициализирует из параметров
   * \param argc - количество аргументов командной строки
   * \param argv - аргументы командной строки
   * \return std::shared_ptr<AbstractParser> - объект парсера комендной строки.
   */
  static std::shared_ptr<AbstractParser> instance(const int& argc = 0, const char** argv = nullptr);

private:
  /*!
   * \brief Приватный конструтор
   * \param argc - количество аргументов командной строки
   * \param argv - аргументы командной строки
   */
  SingletonParser(const int& argc, const char** argv);

private:
  static std::shared_ptr<SingletonParser> mParser; //!< Единственный объект этого типа.

};

} // namespace ProgramOptions

#endif // BASE_PROGRAM_OPTIONS_PARSER_HPP
