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

string DateTextKeys::get_date_time_message(const Date& date, const string& season_sid)
{
  string date_time_message = StringTable::get(DateTextKeys::DATE_TIME_MESSAGE);
  string season = StringTable::get(season_sid);
  
  string time = DateTextKeys::get_time(date);
  string day_of_week = StringTable::get(date.get_day_of_week_sid());
  string month = StringTable::get(date.get_month_sid());  

  boost::replace_first(date_time_message, "%s", time);
  boost::replace_first(date_time_message, "%s", day_of_week);
  boost::replace_first(date_time_message, "%s", std::to_string(date.get_day_of_month()));
  boost::replace_first(date_time_message, "%s", month);
  boost::replace_first(date_time_message, "%s", std::to_string(date.get_year()));
  boost::replace_first(date_time_message, "%s", season);
  
  return date_time_message;
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
