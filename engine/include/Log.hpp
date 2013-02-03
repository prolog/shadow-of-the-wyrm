#pragma once
#include <string>
#include <fstream>

enum LoggingLevel
{
  LOG_NONE  = 0,
  LOG_ERROR = 1,
  LOG_INFO  = 2,
  LOG_TRACE = 3,
  LOG_DEBUG = 4
};

class Log
{
  public:
    static Log& instance()
    {
      static Log inst;
      return inst;
    }

    void error(const std::string& to_error);
    void log(const std::string& to_log);
    void trace(const std::string& to_trace);
    void debug(const std::string& to_debug);

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
