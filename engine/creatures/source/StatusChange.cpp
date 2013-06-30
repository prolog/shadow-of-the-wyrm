#include "Creature.hpp"
#include "Serialize.hpp"
#include "StatusChange.hpp"

using namespace std;

StatusChange::StatusChange(const double start, const double elapsed)
: start_time(start), time_elapsed(elapsed)
{
}

StatusChange::~StatusChange()
{
}

void StatusChange::tick(CreaturePtr creature) const
{
}

bool StatusChange::serialize(ostream& stream)
{
  Serialize::write_double(stream, start_time);
  Serialize::write_double(stream, time_elapsed);

  return true;
}

bool StatusChange::deserialize(istream& stream)
{
  Serialize::read_double(stream, start_time);
  Serialize::read_double(stream, time_elapsed);

  return true;
}

ClassIdentifier StatusChange::internal_class_identifier() const
{
  return CLASS_ID_STATUS_CHANGE;
}

