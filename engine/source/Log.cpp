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

string Log::create_filename()
{
  string filename_prefix = "sl-";
  string filename_ext = ".log";

  ostringstream filename;
  filename << filename_prefix << counter++ << filename_ext;
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
