#include <chrono>
#include <ctime>
#include <sstream>
#include <limits>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include "Log.hpp"

using namespace std;
using namespace boost;
using namespace boost::posix_time;

LoggingLevel Log::level = LoggingLevel::LOG_NONE; // Logging is off by default.
int Log::counter = 0;
const string Log::LOG_PREFIX = "sotw-";

Log::Log()
{
  string filename = create_filename();
  while (filesystem::exists(filename) && (counter != numeric_limits<int>::max()))
  {
    filename = create_filename();
  }

  sl_log.open(filename.c_str(), ios::out);
}

Log::~Log()
{
  sl_log.close();
}

bool Log::log_using_level(const LoggingLevel log_level, const string& log_msg)
{
  bool logged = false;

  switch (log_level)
  {
    case LoggingLevel::LOG_TRACE:
      logged = trace(log_msg);
      break;
    case LoggingLevel::LOG_DEBUG:
      logged = debug(log_msg);
      break;
    case LoggingLevel::LOG_INFO:
      logged = log(log_msg);
      break;
    case LoggingLevel::LOG_ERROR:
      logged = error(log_msg);
      break;
    default:
      break;
  }

  return logged;
}

bool Log::error(const string& to_error)
{
  bool logged = false;

  if (level <= LoggingLevel::LOG_ERROR)
  {
    sl_log << create_datetimestamp() << "\t" << to_error << endl;
    logged = true;
  }

  return logged;
}

bool Log::log(const string& to_log)
{
  bool logged = false;

  if (level <= LoggingLevel::LOG_INFO)
  {
    sl_log << create_datetimestamp() << "\t" << to_log << endl;
    logged = true;
  }

  return logged;
}

bool Log::debug(const string& to_debug)
{
  bool logged = false;

  if (level <= LoggingLevel::LOG_DEBUG)
  {
    sl_log << create_datetimestamp() << "\t" << to_debug << endl;
    logged = true;
  }

  return logged;
}

bool Log::trace(const string& to_trace)
{
  bool logged = false;

  if (level <= LoggingLevel::LOG_TRACE)
  {
    sl_log << create_datetimestamp() << "\t" << to_trace << endl;
    logged = true;
  }

  return logged;
}

bool Log::level_enabled(const LoggingLevel ll) const
{
  return (level <= ll);
}

bool Log::error_enabled() const
{
  return level_enabled(LoggingLevel::LOG_ERROR);
}

bool Log::info_enabled() const
{
  return level_enabled(LoggingLevel::LOG_INFO);
}

bool Log::debug_enabled() const
{
  return level_enabled(LoggingLevel::LOG_DEBUG);
}

bool Log::trace_enabled() const
{
  return level_enabled(LoggingLevel::LOG_TRACE);
}

string Log::create_filename()
{
  string filename_ext = ".log";
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);

  struct tm *parts = std::localtime(&now_c);
  ostringstream filename;
  filename << "logs/" << LOG_PREFIX;
  filename << (1900 + parts->tm_year);

  int mon = 1 + parts->tm_mon;

  if (mon <= 9)
  {
    filename << 0;
  }

  filename << mon;
  
  int day = parts->tm_mday;
  
  if (day <= 9)
  {
    filename << 0;
  }
  
  filename << day;

  filename << "-" << ++counter << filename_ext;
  return filename.str();
}

string Log::create_datetimestamp()
{
  ptime now = second_clock::local_time();
  return to_simple_string(now);
}

void Log::set_log_level(const LoggingLevel new_level)
{
  level = new_level;
}
