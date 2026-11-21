#include <chrono>
#include <ctime>
#include <filesystem>
#include "Conversion.hpp"
#include "LogFiles.hpp"
#include "Log.hpp"

using namespace std;
using namespace std::filesystem;

int LogFiles::remove_old(const int days_old)
{
  int removed = 0;
  string p = "logs";
  std::filesystem::path local_dir(p);
  std::filesystem::directory_iterator end_it;

  if (std::filesystem::exists(local_dir))
  {
    for (std::filesystem::directory_iterator d_it(local_dir); d_it != end_it; d_it++)
    {
      // Make sure we only consider .log files that start with sotw, for
      // extra safety.
      if (std::filesystem::is_regular_file(*d_it) && (d_it->path().filename().string().find(Log::LOG_PREFIX) == 0) && d_it->path().extension() == ".log")
      {
        time_t now_time = time(0);
        std::filesystem::file_time_type tm = std::filesystem::last_write_time(d_it->path());
        const auto stt_time = Convert::to_time_t(tm);

        string fname = d_it->path().string();

        double time_diff = difftime(now_time, stt_time);
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
