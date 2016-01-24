#include "Calendar.hpp"
#include "Date.hpp"
#include "SeasonFactory.hpp"
#include "Serialize.hpp"

using namespace std;

Calendar::Calendar()
: seconds(12960000), STARTING_YEAR(832)
{
  // Set a default season.
  season = SeasonFactory::create_season(Season::SEASON_WINTER);

  // Overwrite the default season, if the current date is out of synch.
  update_season_if_necessary();
}

bool Calendar::operator==(const Calendar& c) const
{
  bool result = true;

  result = result && (seconds == c.seconds);
  result = result && (STARTING_YEAR == c.STARTING_YEAR);
  result = result && season && c.season && (*season == *c.season);
  result = result && calendar_days == c.calendar_days;

  return result;
}

void Calendar::set_date(const uint days_elapsed)
{
  seconds = (days_elapsed) * 60 * 60 * 24;
  uint month_of_year = (days_elapsed / DateValues::NUMBER_OF_DAYS_PER_MONTH);
  season = SeasonFactory::create_season(month_of_year);
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

double Calendar::get_seconds() const
{
  return seconds;
}

double Calendar::get_seconds_from_date(const Date& date) const
{
  double secs = 0;

  secs = date.get_seconds() +
         (date.get_minutes() * 60) +
         (date.get_hours() * 60 * 60) +
         (date.get_day_of_month() * 60 * 60 * 24) +
         (date.get_month() * 60 * 60 * 24 * 30) +
         ((date.get_year() - STARTING_YEAR) * 60 * 60 * 24 * 30 * 12);

  return secs;
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
  uint day_month = (total_days_elapsed % DateValues::NUMBER_OF_DAYS_PER_MONTH) + 1 /* Days of month start at 1, too */;
  uint month = ((total_days_elapsed / DateValues::NUMBER_OF_DAYS_PER_MONTH) % 12);
  uint year = STARTING_YEAR + (total_days_elapsed / DateValues::NUMBER_OF_DAYS_PER_YEAR); /* 30 * 12 */

  Date calculated_date(sec, min, hr, day_week, day_month, month, year);
  return calculated_date;
}

ISeasonPtr Calendar::get_season() const
{
  return season;
}

uint Calendar::get_starting_year() const
{
  return STARTING_YEAR;
}

bool Calendar::update_season_if_necessary()
{
  bool season_updated = false;
  Date date = get_date();
  uint month = date.get_month();
  
  // If the current month is now outside of the current season's
  // months, increment the season.
  //
  // The while-loop is so that I can set an arbitrary number of
  // seconds to start the clock at a particular point, and have the
  // season adjust.  In theory, this should not be dangerous.
  //
  // In theory.
  set<Months> months = season->get_months_in_season();

  while (months.find(static_cast<Months>(month)) == months.end())
  {
    season = SeasonFactory::create_season(season->get_next_season());
    season_updated = true;

    months = season->get_months_in_season();
  }
  
  return season_updated;
}

void Calendar::set_calendar_days(const map<int, CalendarDay>& new_calendar_days)
{
  calendar_days = new_calendar_days;
}

map<int, CalendarDay>& Calendar::get_calendar_days_ref()
{
  return calendar_days;
}

bool Calendar::serialize(ostream& stream) const
{
  Serialize::write_double(stream, seconds);
  Serialize::write_uint(stream, STARTING_YEAR);

  Serialize::write_class_id(stream, season->get_class_identifier());
  season->serialize(stream);

  Serialize::write_size_t(stream, calendar_days.size());

  for (const auto& cd_pair : calendar_days)
  {
    Serialize::write_int(stream, cd_pair.first);
    cd_pair.second.serialize(stream);
  }

  return true;
}

bool Calendar::deserialize(istream& stream)
{
  Serialize::read_double(stream, seconds);
  Serialize::read_uint(stream, STARTING_YEAR);

  ClassIdentifier season_ci;
  Serialize::read_class_id(stream, season_ci);
  season = SeasonFactory::create_season(season_ci);
  if (!season) return false;
  if (!season->deserialize(stream)) return false;

  size_t cal_size = 0;
  Serialize::read_size_t(stream, cal_size);

  for (size_t i = 0; i < cal_size; i++)
  {
    int day_of_year = -1;
    Serialize::read_int(stream, day_of_year);

    CalendarDay day_info;
    day_info.deserialize(stream);

    calendar_days[day_of_year] = day_info;
  }

  return true;
}

ClassIdentifier Calendar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CALENDAR;
}

#ifdef UNIT_TESTS
#include "unit_tests/Calendar_test.cpp"
#endif

