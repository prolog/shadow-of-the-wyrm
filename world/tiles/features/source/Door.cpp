#include "Door.hpp"
#include "StringConstants.hpp"

using std::string;

// This constructor is really only used by serialization.
Door::Door()
{
}

// By default, doors are made of wood.
Door::Door(LockPtr new_lock, const EntranceState& new_state)
: Entrance(new_lock, new_state)
{
}

Feature* Door::clone()
{
  return new Door(*this);
}

bool Door::handle()
{
  bool result = false;

  LockPtr lock = get_lock();
  EntranceState& entrance_state = get_state_ref();
  EntranceStateType state = entrance_state.get_state();

  switch (state)
  {
    // If the door is smashed, nothing can be done.
    case ENTRANCE_TYPE_DESTROYED:
      break;

    case ENTRANCE_TYPE_OPEN:
      result = close();
      break;

    case ENTRANCE_TYPE_CLOSED:
      // If the door is closed and locked, try to unlock it.
      // If the door is closed and unlocked, open it.
    default:
      result = open();
      break;
  }

  return result;
}

bool Door::kick()
{
  // If the door is smashed or open, kick at the air.
  // If the door is shut, kick it.
  //   - Check for traps.
  return true;
}

bool Door::get_is_blocking() const
{
  // Only closed doors are blocking.
  return (state.get_state() == ENTRANCE_TYPE_CLOSED);
}

uchar Door::get_symbol() const
{
  return state.get_symbol();
}

string Door::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_DOOR;
}

ClassIdentifier Door::internal_class_identifier() const
{
  return CLASS_ID_DOOR;
}
