#pragma once
#include <string>
#include <fstream>

enum LoggingLevel
{
  LOG_LOWEST = 0,
  LOG_TRACE = 0,
  LOG_DEBUG = 1,
  LOG_INFO  = 2,
  LOG_ERROR = 3,
  LOG_NONE  = 4,
  LOG_HIGHEST = 4
};

#define CLOG_TRACE 0
#define CLOG_DEBUG 1
#define CLOG_INFO 2
#define CLOG_ERROR 3

class Log
{
  public:
    static Log& instance()
    {
      static Log inst;
      return inst;
    }

    bool log_using_level(const LoggingLevel level, const std::string& log_msg);
    bool error(const std::string& to_error);
    bool log(const std::string& to_log);
    bool trace(const std::string& to_trace);
    bool debug(const std::string& to_debug);

  private:
    friend int main(int argc, char* argv[]);
    static Log* instance(const LoggingLevel level_to_set);
    Log(); // Open file
    ~Log(); // Close generated file
    Log(const Log& log); // Do not implement.
    bool operator=(const Log& log); // Do not implement.

    static void set_log_level(const LoggingLevel);

    std::string create_filename();
    std::string create_datetimestamp();

    static LoggingLevel level;
    static int counter;
    std::ofstream sl_log;
};
