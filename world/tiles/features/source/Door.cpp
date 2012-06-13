#include "Door.hpp"
#include "StringConstants.hpp"

using std::string;

// By default, doors are made of wood.
Door::Door(LockPtr new_lock, const EntranceState& new_state)
: Entrance(new_lock, new_state)
{
}

bool Door::handle()
{
  // If the door is smashed, display a message.
  // If the door is open, close it.
  // If the door is closed and locked, try to unlock it.
  // If the door is closed and unlocked, open it.
  return true;
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
