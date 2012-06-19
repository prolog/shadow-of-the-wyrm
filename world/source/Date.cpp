#include "Date.hpp"

Date::Date(const uint sec, const uint min, const uint hrs, const uint day_week, const uint day_month, const uint mnth, const uint yr)
: seconds(sec), minutes(min), hours(hrs), day_of_week(day_week), day_of_month(day_month), month(mnth), year(yr)
{
}

uint Date::get_seconds() const
{
  return seconds;
}

uint Date::get_minutes() const
{
  return minutes;
}

uint Date::get_hours() const
{
  return hours;
}

uint Date::get_day_of_week() const
{
  return day_of_week;
}

uint Date::get_day_of_month() const
{
  return day_of_month;
}

uint Date::get_month() const
{
  return month;
}

uint Date::get_year() const
{
  return year;
}
