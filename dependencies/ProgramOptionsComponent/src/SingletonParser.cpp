#include <Base/ProgramOptions/SingletonParser.hpp>
#include <iostream>

namespace ProgramOptions {

std::shared_ptr<SingletonParser> SingletonParser::mParser;

SingletonParser::SingletonParser(const int& argc, const char** argv)
  : AbstractParser(argc,argv)
{}

std::shared_ptr<AbstractParser> SingletonParser::instance(const int& argc, const char** argv)
{
  if(!mParser)
  {
    assert(argv);
    return mParser = std::make_shared<SingletonParser>(SingletonParser(argc, argv));
  }

  if(argv)
    std::cerr << "argv multiple definition" << std::endl;
  return mParser;
}

} // namespace ProgramOptions
