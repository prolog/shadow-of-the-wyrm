#include "Date.hpp"

using namespace std;

const uint TimeOfDay::TIME_OF_DAY_DAWN = 7;
const uint TimeOfDay::TIME_OF_DAY_DAY = 8;
const uint TimeOfDay::TIME_OF_DAY_DUSK = 19;
const uint TimeOfDay::TIME_OF_DAY_NIGHT = 20;

std::map<TimeOfDayType, std::pair<Colour, Colour>> TimeOfDay::time_of_day_colour_overrides;

pair<Colour, Colour> TimeOfDay::get_time_of_day_colours(const TimeOfDayType tod, const bool on_overworld_map)
{
  if (time_of_day_colour_overrides.empty())
  {
    initialize_colour_overrides();
  }

  pair<Colour, Colour> overrides = make_pair(Colour::COLOUR_UNDEFINED, Colour::COLOUR_UNDEFINED);
  auto t_it = time_of_day_colour_overrides.find(tod);

  if (on_overworld_map && t_it != time_of_day_colour_overrides.end())
  {
    overrides = t_it->second;
  }

  return overrides;
}

pair<bool, TimeOfDayType> TimeOfDay::get_is_transition_hour(const uint hour)
{
  if (hour == TIME_OF_DAY_DAWN)
  {
    return make_pair(true, TimeOfDayType::TIME_OF_DAY_DAWN);
  }
  else if (hour == TIME_OF_DAY_DAY)
  {
    return make_pair(true, TimeOfDayType::TIME_OF_DAY_DAY);
  }
  else if (hour == TIME_OF_DAY_DUSK)
  { 
    return make_pair(true, TimeOfDayType::TIME_OF_DAY_DUSK);
  }
  else if (hour == TIME_OF_DAY_NIGHT)
  {
    return make_pair(true, TimeOfDayType::TIME_OF_DAY_NIGHT);
  }

  return make_pair(false, TimeOfDayType::TIME_OF_DAY_UNDEFINED);
}

void TimeOfDay::initialize_colour_overrides()
{
  time_of_day_colour_overrides.clear();

  time_of_day_colour_overrides = { {TimeOfDayType::TIME_OF_DAY_NIGHT, make_pair(Colour::COLOUR_BLUE, Colour::COLOUR_BOLD_CYAN)},
                                   {TimeOfDayType::TIME_OF_DAY_DAWN, make_pair(Colour::COLOUR_RED, Colour::COLOUR_BOLD_RED)},
                                   {TimeOfDayType::TIME_OF_DAY_DUSK, make_pair(Colour::COLOUR_YELLOW, Colour::COLOUR_BOLD_YELLOW)} };
}

string Date::month_sids[DateValues::NUMBER_OF_MONTHS] = {"MONTH_1", "MONTH_2", "MONTH_3", "MONTH_4", "MONTH_5", "MONTH_6", "MONTH_7", "MONTH_8", "MONTH_9", "MONTH_10", "MONTH_11", "MONTH_12"};
string Date::day_of_week_sids[DateValues::NUMBER_OF_DAYS] = {"DAY_1", "DAY_2", "DAY_3", "DAY_4", "DAY_5", "DAY_6", "DAY_7"};

Date::Date(const uint sec, const uint min, const uint hrs, const uint day_week, const uint day_month, const uint day_year, const uint mnth, const uint yr)
: seconds(sec), minutes(min), hours(hrs), day_of_week(day_week), day_of_month(day_month), day_of_year(day_year), month(mnth), year(yr)
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

TimeOfDayType Date::get_time_of_day() const
{
  TimeOfDayType dtype = TimeOfDayType::TIME_OF_DAY_NIGHT;

  if (hours >= TimeOfDay::TIME_OF_DAY_DAWN && hours < TimeOfDay::TIME_OF_DAY_DAY)
  {
    dtype = TimeOfDayType::TIME_OF_DAY_DAWN;
  }
  else if (hours >= TimeOfDay::TIME_OF_DAY_DAY && hours < TimeOfDay::TIME_OF_DAY_DUSK)
  {
    dtype = TimeOfDayType::TIME_OF_DAY_DAY;
  }
  else if (hours >= TimeOfDay::TIME_OF_DAY_DUSK && hours < TimeOfDay::TIME_OF_DAY_NIGHT)
  {
    dtype = TimeOfDayType::TIME_OF_DAY_DUSK;
  }

  return dtype;
}

uint Date::get_day_of_week() const
{
  return day_of_week;
}

string Date::get_day_of_week_sid() const
{
  return day_of_week_sids[day_of_week];
}

uint Date::get_day_of_month() const
{
  return day_of_month;
}

uint Date::get_day_of_year() const
{
  return day_of_year;
}

uint Date::get_month() const
{
  return month;
}

string Date::get_month_sid() const
{
  return month_sids[month];
}

uint Date::get_year() const
{
  return year;
}

#ifdef UNIT_TESTS
#include "unit_tests/Date_test.cpp"
#endif
