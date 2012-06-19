#include "Calendar.hpp"
#include "Date.hpp"

Calendar::Calendar()
: seconds(0), STARTING_YEAR(832)
{
}

void Calendar::add_days(const uint days)
{
  double ddays = static_cast<double>(days);
  add_seconds(ddays * 8600);
}
void Calendar::add_seconds(const double additional_seconds)
{
  seconds += additional_seconds;
}

// Calculate and return the date, based on the total seconds that have elapsed so far.
Date Calendar::get_date() const
{
  uint usec = static_cast<uint>(seconds);
  uint sec = usec % 60;
  uint min = (usec / 60) % 60;
  uint hr  = ((usec / 60) / 60) % 24;
  uint total_days_elapsed = (usec / 86400);
  uint day_week = (total_days_elapsed % 7) + 1 /* Week starts at day 1 */;
  uint day_month = (total_days_elapsed % 30) + 1 /* Days of month start at 1, too */;
  uint month = ((total_days_elapsed / 30) % 12) + 1; /* Month, too.  There will be a map provided to look up the name, based on the value. */
  uint year = STARTING_YEAR + (total_days_elapsed / 365);

  Date calculated_date(sec, min, hr, day_week, day_month, month, year);
  return calculated_date;
}
