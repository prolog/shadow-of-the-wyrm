#include <sstream>
#include <limits>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include "Log.hpp"

using namespace std;
using namespace boost;
using namespace boost::posix_time;

LoggingLevel Log::level = LOG_NONE; // Logging is off by default.
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

void Log::error(const string& to_error)
{
  if (level >= LOG_ERROR)
  {
    sl_log << create_datetimestamp() << "\t" << to_error << endl;
  }
}

void Log::log(const string& to_log)
{
  if (level >= LOG_INFO)
  {
    sl_log << create_datetimestamp() << "\t" << to_log << endl;
  }
}

void Log::trace(const string& to_trace)
{
  if (level >= LOG_TRACE)
  {
    sl_log << create_datetimestamp() << "\t" << to_trace << endl;
  }
}

void Log::debug(const string& to_debug)
{
  if (level >= LOG_DEBUG)
  {
    sl_log << create_datetimestamp() << "\t" << to_debug << endl;
  }
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
