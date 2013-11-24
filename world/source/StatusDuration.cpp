#include "Serialize.hpp"
#include "StatusDuration.hpp"
#include "global_prototypes.hpp"

using namespace std;

StatusDuration::StatusDuration()
: end(0)
{
}

StatusDuration::StatusDuration(const double end_dur)
: end(end_dur)
{
}

bool StatusDuration::operator==(const StatusDuration& sd) const
{
  bool result = true;

  result = result && (dequal(end, sd.end));

  return result;
}

void StatusDuration::set_end(const double new_end_val)
{
  end = new_end_val;
}

double StatusDuration::get_end() const
{
  return end;
}

bool StatusDuration::serialize(ostream& stream) const
{
  Serialize::write_double(stream, end);

  return true;
}

bool StatusDuration::deserialize(istream& stream)
{
  Serialize::read_double(stream, end);

  return true;
}

ClassIdentifier StatusDuration::internal_class_identifier() const
{
  return CLASS_ID_STATUS_DURATION;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatusDuration_test.cpp"
#endif

