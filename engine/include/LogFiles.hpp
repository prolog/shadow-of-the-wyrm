#pragma once

class LogFiles
{
  public:
    // Remove log files older than the given number of days.
    // Return value is the number of logs removed.
    int remove_old(const int days_old);
};
