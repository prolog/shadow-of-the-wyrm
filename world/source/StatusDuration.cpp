#include "Serialize.hpp"
#include "StatusDuration.hpp"

using namespace std;

StatusDuration::StatusDuration()
: start_time(0), duration_length(0)
{
}

StatusDuration::StatusDuration(const ulonglong start, const ulonglong duration)
: start_time(start), duration_length(duration)
{
}

bool StatusDuration::operator==(const StatusDuration& sd) const
{
  bool result = true;

  result = result && (start_time == sd.start_time);
  result = result && (duration_length == sd.duration_length);

  return result;
}

void StatusDuration::set_start_time(const ulonglong new_start_time)
{
  start_time = new_start_time;
}

ulonglong StatusDuration::get_start_time() const
{
  return start_time;
}

void StatusDuration::set_duration_length(const ulonglong new_duration)
{
  duration_length = new_duration;
}

ulonglong StatusDuration::get_duration_length() const
{
  return duration_length;
}

bool StatusDuration::serialize(ostream& stream)
{
  Serialize::write_ulonglong(stream, start_time);
  Serialize::write_ulonglong(stream, duration_length);

  return true;
}

bool StatusDuration::deserialize(istream& stream)
{
  Serialize::read_ulonglong(stream, start_time);
  Serialize::read_ulonglong(stream, duration_length);

  return true;
}

ClassIdentifier StatusDuration::internal_class_identifier() const
{
  return CLASS_ID_STATUS_DURATION;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatusDuration_test.cpp"
#endif

