#include "Calendar.hpp"
#include "Date.hpp"
#include "SeasonFactory.hpp"

using std::set;

Calendar::Calendar()
: seconds(0), STARTING_YEAR(832)
{
  season = SeasonFactory::create_season(SEASON_WINTER);
}

void Calendar::add_days(const uint days)
{
  double ddays = static_cast<double>(days);
  add_seconds(ddays * 86400);
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
  uint day_week = (total_days_elapsed % 7);
  uint day_month = (total_days_elapsed % 30) + 1 /* Days of month start at 1, too */;
  uint month = ((total_days_elapsed / 30) % 12);
  uint year = STARTING_YEAR + (total_days_elapsed / 365);

  Date calculated_date(sec, min, hr, day_week, day_month, month, year);
  return calculated_date;
}

ISeasonPtr Calendar::get_season() const
{
  return season;
}

void Calendar::update_season_if_necessary()
{
  Date date = get_date();
  uint month = date.get_month();
  
  set<Months> months = season->get_months_in_season();
  
  // If the current month is now outside of the current season's
  // months, increment the season.
  if (months.find(static_cast<Months>(month)) == months.end())
  {
    season = SeasonFactory::create_season(season->get_next_season());
  }
}

