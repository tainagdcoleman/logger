#include<logger.h>
#include<string>
#include "boost/log/trivial.hpp"
#include "boost/log/utility/setup.hpp"


using namespace std;

Logger::Logger(bool console, string file)
  :console(console)
  ,file(file)
{
      static const std::string COMMON_FMT("[%TimeStamp%][%Severity%]:  %Message%");

      boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

      // Output message to console
      boost::log::add_console_log(
          std::cout,
          boost::log::keywords::format = COMMON_FMT,
          boost::log::keywords::auto_flush = true
      );

      // Output message to file, rotates when file reached 1mb or at midnight every day. Each log file
      // is capped at 1mb and total is 20mb
      boost::log::add_file_log (
          boost::log::keywords::file_name = "sample_%3N.log",
          boost::log::keywords::rotation_size = 1 * 1024 * 1024,
          boost::log::keywords::max_size = 20 * 1024 * 1024,
          boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
          boost::log::keywords::format = COMMON_FMT,
          boost::log::keywords::auto_flush = true
      );

      boost::log::add_common_attributes();

      // Only output message with INFO or higher severity in Release
  #ifndef _DEBUG
      boost::log::core::get()->set_filter(
          boost::log::trivial::severity >= boost::log::trivial::info
      );
  #endif

}

//static methods

Logger Logger::getLogger()
{
  is_init = true;
  static Logger logger(console, file); // constructor -- first run, gets set up, second +  it will just return (singleton)
  return logger;
}

void Logger::init(bool console, string file, Logger::Levels severity)
{
  if (!is_init)
  {
    Logger::console = console;
    Logger::file = file;

    switch (severity)
    {
      case Logger::Levels::TRACE:
        Logger::severity = boost::log::trivial::trace;
        break;
      case Logger::Levels::DEBUG:
        Logger::severity = boost::log::trivial::debug;
        break;
      case Logger::Levels::INFO:
        Logger::severity = boost::log::trivial::info;
        break;
      case Logger::Levels::WARNING:
        Logger::severity = boost::log::trivial::warning;
        break;
      case Logger::Levels::ERROR:
        Logger::severity = boost::log::trivial::error;
        break;
      case Logger::Levels::FATAL:
        Logger::severity = boost::log::trivial::fatal;
        break;    
    }

  }
}
