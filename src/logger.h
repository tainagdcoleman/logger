#include<string>
#include "boost/log/trivial.hpp"


enum Levels{TRACE, DEBUG, INFO, WARNING, ERROR, FATAL};

using namespace std;
class Logger
{
private:
    static string file;
    static bool console;
    static bool is_init;
    static Levels severity;

    Logger();
    Logger(Logger const&);
    void operator=(Logger const&);

public:
  void log(string src, string msg, Levels severity);
  static Logger getLogger();
  static void init(bool console, string file, Levels severity);

  //Logger(Logger const&) = delete;
  //void operator=(Logger const&) = delete;

};
