#include "Entrance.hpp"
#include "Serialize.hpp"

using namespace std;

// This constructor is only used by the serialization code
Entrance::Entrance()
: Feature(MATERIAL_TYPE_WOOD)
{
}

Entrance::Entrance(LockPtr new_lock, const EntranceState& new_state)
: Feature(MATERIAL_TYPE_WOOD), state(new_state)
{
  set_lock(new_lock);
}

bool Entrance::operator==(const Entrance& entr)
{
  bool result = Feature::operator==(entr);

  result = result && (state == entr.state);
  result = result && (maximum_size == entr.maximum_size);

  return result;
}

void Entrance::set_state(const EntranceState& new_state)
{
  state = new_state;
}

EntranceState Entrance::get_state() const
{
  return state;
}

EntranceState& Entrance::get_state_ref()
{
  return state;
}

void Entrance::set_maximum_size(const CreatureSize new_size)
{
  maximum_size = new_size;
}

CreatureSize Entrance::get_maximum_size() const
{
  return maximum_size;
}

bool Entrance::can_open() const
{
  return true;
}

bool Entrance::serialize(ostream& stream)
{
  if (lock)
  {
    Serialize::write_class_id(stream, lock->get_class_identifier());
    lock->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  state.serialize(stream);

  return true;
}

bool Entrance::deserialize(istream& stream)
{
  ClassIdentifier class_id;
  Serialize::read_class_id(stream, class_id);

  if (class_id != CLASS_ID_NULL)
  {
    lock = LockPtr(new Lock());
    lock->deserialize(stream);
  }
  state.deserialize(stream);

  return true;
}

ClassIdentifier Entrance::internal_class_identifier() const
{
  return CLASS_ID_ENTRANCE;
}

#ifdef UNIT_TESTS
#include "unit_tests/AllEntrances_test.cpp"
#endif


