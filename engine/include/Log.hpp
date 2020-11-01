#pragma once
#include <string>
#include <fstream>

enum struct LoggingLevel
{
  LOG_LOWEST = 0,
  LOG_TRACE = 0,
  LOG_DEBUG = 1,
  LOG_INFO  = 2,
  LOG_ERROR = 3,
  LOG_NONE  = 4,
  LOG_HIGHEST = 4
};

constexpr auto CLOG_TRACE = 0;
constexpr auto CLOG_DEBUG = 1;
constexpr auto CLOG_INFO = 2;
constexpr auto CLOG_ERROR = 3;

class Log
{
  public:
    static Log& instance()
    {
      static Log inst;
      return inst;
    }

    void set_log_level(const LoggingLevel);

    bool log_using_level(const LoggingLevel level, const std::string& log_msg);
    bool error(const std::string& to_error);
    bool log(const std::string& to_log);
    bool debug(const std::string& to_debug);
    bool trace(const std::string& to_trace);

    bool level_enabled(const LoggingLevel level) const;
    bool error_enabled() const;
    bool info_enabled() const;
    bool debug_enabled() const;
    bool trace_enabled() const;

  private:
    friend class LogFiles;
    friend int main(int argc, char* argv[]);
    static Log* instance(const LoggingLevel level_to_set);
    Log(); // Open file
    ~Log(); // Close generated file
    Log(const Log& log); // Do not implement.
    bool operator=(const Log& log); // Do not implement.

    std::string create_filename();
    std::string create_datetimestamp();

    static LoggingLevel level;
    static int counter;
    static const std::string LOG_PREFIX;
    std::ofstream sl_log;
};
