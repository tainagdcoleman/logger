#include "logger.h"
#include <string>
#include "boost/log/trivial.hpp"
#include "boost/log/utility/setup.hpp"


using namespace std;


string file = "";
bool console = true;
bool is_init = false;
Levels severity = Levels::INFO;

Logger::Logger(bool console, string file)
  :console(console)
  ,file(file)
{
      static const string COMMON_FMT("[%TimeStamp%][%Severity%]:  %Message%");

      boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

      if(console)
      {
        // Output message to console
        boost::log::add_console_log(
            std::cout,
            boost::log::keywords::format = COMMON_FMT,
            boost::log::keywords::auto_flush = true
        );
      }
      if(file != "")
      {
      // Output message to file, rotates when file reached 1mb or at midnight every day. Each log file
      // is capped at 1mb and total is 20mb
        boost::log::add_file_log (
            boost::log::keywords::file_name = file,
            boost::log::keywords::rotation_size = 1 * 1024 * 1024,
            boost::log::keywords::max_size = 20 * 1024 * 1024,
            boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
            boost::log::keywords::format = COMMON_FMT,
            boost::log::keywords::auto_flush = true
        );
      }
      boost::log::add_common_attributes();

      auto filter_severity = boost::log::trivial::trace;
      switch (Logger::severity)
      {
        case Levels::DEBUG:
          filter_severity = boost::log::trivial::debug;
          break;
        case Levels::INFO:
          filter_severity = boost::log::trivial::info;
          break;
        case Levels::WARNING:
          filter_severity = boost::log::trivial::warning;
          break;
        case Levels::ERROR:
          filter_severity = boost::log::trivial::error;
          break;
        case Levels::FATAL:
          filter_severity = boost::log::trivial::fatal;
          break;
      }

      boost::log::core::get()->set_filter(
          boost::log::trivial::severity >= filter_severity;
      );

}

void Logger::log(string src, string msg, Levels severity)
{
  string message = string("From " + src + ", " + msg)
  switch(severity)
  {
    case Levels::TRACE:
      BOOST_LOG_TRIVIAL(trace) << message;
      break;
    case Levels::DEBUG:
      BOOST_LOG_TRIVIAL(debug) << message;
      break;
    case Levels::INFO:
      BOOST_LOG_TRIVIAL(info) << message;
      break;
    case Levels::WARNING:
      BOOST_LOG_TRIVIAL(warning) << message;
      break;
    case Levels::ERROR:
      BOOST_LOG_TRIVIAL(error) << message;
      break;
    case Levels::FATAL:
      BOOST_LOG_TRIVIAL(fatal) << message;
      break;

  }

}
//static methods

Logger Logger::getLogger()
{
  is_init = true;
  static Logger logger(console, file); // constructor -- first run, gets set up, second +  it will just return (singleton)
  return logger;
}

void Logger::init(bool console, string file, Levels severity)
{
  if (!is_init)
  {
    Logger::console = console;
    Logger::file = file;
    Logger::severity = severity;

  }
}
