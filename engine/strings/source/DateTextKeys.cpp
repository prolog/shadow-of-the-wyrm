#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "Conversion.hpp"
#include "DateTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Date/time
DateTextKeys::DateTextKeys()
{
}

DateTextKeys::~DateTextKeys()
{
}

const string DateTextKeys::DATE_TIME_MESSAGE = "DATE_TIME_MESSAGE";
const string DateTextKeys::DATE_TIME_WEATHER_MESSAGE = "DATE_TIME_WEATHER_MESSAGE";

string DateTextKeys::get_date_time_message(const Date& date)
{
  string dt = StringTable::get(DateTextKeys::DATE_TIME_MESSAGE);

  string time = DateTextKeys::get_time(date);
  string day = std::to_string(date.get_day_of_month());
  string month = StringTable::get(date.get_month_sid());
  string year = std::to_string(date.get_year());

  boost::replace_first(dt, "%s1", time);
  boost::replace_first(dt, "%s2", day);
  boost::replace_first(dt, "%s3", month);
  boost::replace_first(dt, "%s4", year);

  return dt;
}

string DateTextKeys::get_date_time_weather_message(const Date& date, const string& season_sid, const PhaseOfMoonType pom, const string& wind_sid)
{
  string dtw_message = StringTable::get(DateTextKeys::DATE_TIME_WEATHER_MESSAGE);
  string season = StringTable::get(season_sid);
 
  std::map<TimeOfDayType, std::string> tod_sids = { {TimeOfDayType::TIME_OF_DAY_DAWN, DateTextKeys::TIME_OF_DAY_DAWN}, {TimeOfDayType::TIME_OF_DAY_DUSK, DateTextKeys::TIME_OF_DAY_DUSK}, {TimeOfDayType::TIME_OF_DAY_DAY, DateTextKeys::TIME_OF_DAY_DAY}, {TimeOfDayType::TIME_OF_DAY_NIGHT, DateTextKeys::TIME_OF_DAY_NIGHT} };
  string time = DateTextKeys::get_time(date);
  string day_or_night = StringTable::get(tod_sids[date.get_time_of_day()]);
  string day_of_week = StringTable::get(date.get_day_of_week_sid());
  string month = StringTable::get(date.get_month_sid());  

  boost::replace_first(dtw_message, "%s", time);
  boost::replace_first(dtw_message, "%s", day_or_night);
  boost::replace_first(dtw_message, "%s", day_of_week);
  boost::replace_first(dtw_message, "%s", std::to_string(date.get_day_of_month()));
  boost::replace_first(dtw_message, "%s", month);
  boost::replace_first(dtw_message, "%s", std::to_string(date.get_year()));
  boost::replace_first(dtw_message, "%s", season);
  boost::replace_first(dtw_message, "%s", StringTable::get(get_phase_of_moon_sid(pom)));
  boost::replace_first(dtw_message, "%s", StringTable::get(wind_sid));

  return dtw_message;
}

string DateTextKeys::get_time(const Date& date)
{
  uint hours = date.get_hours();
  uint minutes = date.get_minutes();
  uint seconds = static_cast<uint>(date.get_seconds());
  
  ostringstream ss;
  
  if (hours < 10)
  {
    ss << "0";
  }
  
  ss << hours << ":";
  
  if (minutes < 10)
  {
    ss << "0";
  }
  
  ss << minutes << ":";
  
  if (seconds < 10)
  {
    ss << "0";
  }
  
  ss << seconds;
  
  return ss.str();
}

string DateTextKeys::get_phase_of_moon_sid(const PhaseOfMoonType pom)
{
  string val;

  switch (pom)
  {
    case PhaseOfMoonType::PHASE_OF_MOON_NEW:
      val = DateTextKeys::PHASE_OF_MOON_NEW;
      break;
    case PhaseOfMoonType::PHASE_OF_MOON_WAXING:
      val = DateTextKeys::PHASE_OF_MOON_WAXING;
      break;
    case PhaseOfMoonType::PHASE_OF_MOON_FULL:
      val = DateTextKeys::PHASE_OF_MOON_FULL;
      break;
    case PhaseOfMoonType::PHASE_OF_MOON_WANING:
      val = DateTextKeys::PHASE_OF_MOON_WANING;
      break;
    case PhaseOfMoonType::PHASE_OF_MOON_NULL:
      break;
  }

  return val;
}

string DateTextKeys::get_wind_sid(const int wind)
{
  string sid;
  
  if (wind <= 1)
  {
    sid = WIND_CALM;
  }
  else if (wind >= 2 && wind <= 11)
  {
    sid = WIND_LIGHT_BREEZE;
  }
  else if (wind <= 35)
  {
    sid = WIND_STRONG_BREEZE;
  }
  else if (wind <= 65)
  {
    sid = WIND_GALE;
  }
  else
  {
    sid = WIND_STORM;
  }

  return sid;
}

const string DateTextKeys::TIME_OF_DAY_DAY = "TIME_OF_DAY_DAY";
const string DateTextKeys::TIME_OF_DAY_NIGHT = "TIME_OF_DAY_NIGHT";
const string DateTextKeys::TIME_OF_DAY_DAWN = "TIME_OF_DAY_DAWN";
const string DateTextKeys::TIME_OF_DAY_DUSK = "TIME_OF_DAY_DUSK";
const string DateTextKeys::TIME_TRANSITION_DAWN = "TIME_TRANSITION_DAWN";
const string DateTextKeys::TIME_TRANSITION_DAY = "TIME_TRANSITION_DAY";
const string DateTextKeys::TIME_TRANSITION_DUSK = "TIME_TRANSITION_DUSK";
const string DateTextKeys::TIME_TRANSITION_NIGHT = "TIME_TRANSITION_NIGHT";
const string DateTextKeys::PHASE_OF_MOON_NEW = "PHASE_OF_MOON_NEW";
const string DateTextKeys::PHASE_OF_MOON_WAXING = "PHASE_OF_MOON_WAXING";
const string DateTextKeys::PHASE_OF_MOON_FULL = "PHASE_OF_MOON_FULL";
const string DateTextKeys::PHASE_OF_MOON_WANING = "PHASE_OF_MOON_WANING";
const string DateTextKeys::WIND_CALM = "WIND_CALM";
const string DateTextKeys::WIND_LIGHT_BREEZE = "WIND_LIGHT_BREEZE";
const string DateTextKeys::WIND_STRONG_BREEZE = "WIND_STRONG_BREEZE";
const string DateTextKeys::WIND_GALE = "WIND_GALE";
const string DateTextKeys::WIND_STORM = "WIND_STORM";

#ifdef UNIT_TESTS
#include "unit_tests/DateTextKeys_test.cpp"
#endif
