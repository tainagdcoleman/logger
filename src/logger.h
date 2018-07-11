#include<string>
#include "boost/log/trivial.hpp"


using namespace std;
class Logger
{
private:
    static string file;
    static bool console;
    static bool is_init;
    static Logger::Levels severity;

    Logger(bool console, string file);
    Logger(Logger const&);
    void operator=(Logger const&);

public:
  static enum Levels{TRACE, DEBUG, INFO, WARNING, ERROR, FATAL};
  void log(string src, string msg, Logger::Levels severity);
  static Logger getLogger();
  static void init(bool console, string file, string severity);

  Logger(Logger const&) = delete;
  void operator=(Logger const&) = delete;

}
