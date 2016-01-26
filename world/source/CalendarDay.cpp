#include "CalendarDay.hpp"
#include "Serialize.hpp"

using namespace std;

CalendarDay::CalendarDay(const std::string& new_name_sid, const std::string& new_desc_sid, const int new_cal_day)
: name_sid(new_name_sid), description_sid(new_desc_sid), calendar_day(new_cal_day)
{
}

CalendarDay::CalendarDay()
: calendar_day(-1)
{
}

bool CalendarDay::operator==(const CalendarDay& cd) const
{
  bool result = true;

  result = result && (name_sid == cd.name_sid);
  result = result && (description_sid == cd.description_sid);
  result = result && (calendar_day == cd.calendar_day);

  return result;
}

void CalendarDay::set_name_sid(const string& new_name_sid)
{
  name_sid = new_name_sid;
}

string CalendarDay::get_name_sid() const
{
  return name_sid;
}

void CalendarDay::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string CalendarDay::get_description_sid() const
{
  return description_sid;
}

void CalendarDay::set_calendar_day(const int new_calendar_day)
{
  calendar_day = new_calendar_day;
}

int CalendarDay::get_calendar_day() const
{
  return calendar_day;
}

bool CalendarDay::serialize(ostream& stream) const
{
  Serialize::write_string(stream, name_sid);
  Serialize::write_string(stream, description_sid);
  Serialize::write_int(stream, calendar_day);

  return true;
}

bool CalendarDay::deserialize(istream& stream)
{
  Serialize::read_string(stream, name_sid);
  Serialize::read_string(stream, description_sid);
  Serialize::read_int(stream, calendar_day);

  return true;
}

ClassIdentifier CalendarDay::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CALENDAR_DAY;
}

#ifdef UNIT_TESTS
#include "unit_tests/CalendarDay_test.cpp"
#endif

