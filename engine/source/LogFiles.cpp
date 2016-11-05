#include <ctime>
#include <boost/filesystem/operations.hpp>
#include "LogFiles.hpp"
#include "Log.hpp"

using namespace std;
using namespace boost::filesystem;

int LogFiles::remove_old(const int days_old)
{
  int removed = 0;
  string p = ".";
  path local_dir(p);
  directory_iterator end_it;

  if (exists(local_dir))
  {
    for (directory_iterator d_it(local_dir); d_it != end_it; d_it++)
    {
      // Make sure we only consider .log files that start with sotw, for
      // extra safety.
      if (is_regular_file(*d_it) && (d_it->path().filename().string().find(Log::LOG_PREFIX) == 0) && d_it->path().extension() == ".log")
      {
        time_t now_time = time(0);
        std::time_t tm = boost::filesystem::last_write_time(d_it->path());

        string fname = d_it->path().string();

        double time_diff = difftime(now_time, tm);
        int days = static_cast<int>(time_diff / 86400);

        if (days > days_old)
        {
          remove(d_it->path());
        }
      }
    }
  }


  return removed;
}