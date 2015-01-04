#include "ActionTextKeys.hpp"
#include "Entrance.hpp"
#include "Serialize.hpp"

using namespace std;

// This constructor is only used by the serialization code
Entrance::Entrance()
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Entrance::Entrance(LockPtr new_lock, const EntranceState& new_state)
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL), state(new_state)
{
  set_lock(new_lock);
}

bool Entrance::operator==(const Entrance& entr) const
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

bool Entrance::can_handle(const bool feature_tile_occupied) const
{
  // entrances can only be handled if the space is not occupied.
  return (!feature_tile_occupied);
}

bool Entrance::can_open() const
{
  return true;
}

bool Entrance::can_lock() const
{
  return true;
}

bool Entrance::open()
{
  bool result = false;

  EntranceState& state = get_state_ref();

  if (state.get_state() == EntranceStateType::ENTRANCE_TYPE_CLOSED)
  {
    state.set_state(EntranceStateType::ENTRANCE_TYPE_OPEN);
    result = true;
  }

  return result;
}

bool Entrance::close()
{
  bool result = false;

  EntranceState& state = get_state_ref();

  if (state.get_state() == EntranceStateType::ENTRANCE_TYPE_OPEN)
  {
    state.set_state(EntranceStateType::ENTRANCE_TYPE_CLOSED);
    result = true;
  }

  return result;
}

string Entrance::get_handle_message_sid() const
{
  string handle_message_sid;
  EntranceStateType entrance_state = state.get_state();

  switch (entrance_state)
  {
    case EntranceStateType::ENTRANCE_TYPE_DESTROYED:
      handle_message_sid = ActionTextKeys::ACTION_DOOR_DESTROYED;
      break;
    case EntranceStateType::ENTRANCE_TYPE_OPEN:
      handle_message_sid = ActionTextKeys::ACTION_OPEN_DOOR;
      break;
    case EntranceStateType::ENTRANCE_TYPE_CLOSED:
    default:
      handle_message_sid = ActionTextKeys::ACTION_CLOSE_DOOR;
      break;
  }

  return handle_message_sid;
}

bool Entrance::serialize(ostream& stream) const
{
  Feature::serialize(stream);

  // Entrance-specific values.
  state.serialize(stream);
  Serialize::write_enum(stream, maximum_size);

  return true;
}

bool Entrance::deserialize(istream& stream)
{
  Feature::deserialize(stream);

  // Entrance-specific values.
  state.deserialize(stream);
  Serialize::read_enum(stream, maximum_size);

  return true;
}

ClassIdentifier Entrance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ENTRANCE;
}

#ifdef UNIT_TESTS
#include "unit_tests/AllEntrances_test.cpp"
#endif


