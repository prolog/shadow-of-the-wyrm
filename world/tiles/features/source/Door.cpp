#include "Door.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

// This constructor is really only used by serialization.
Door::Door(const Symbol& new_symbol)
: Entrance(new_symbol)
{
}

// By default, doors are made of wood.
Door::Door(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state)
: Entrance(new_symbol, new_lock, new_state)
{
}

Feature* Door::clone()
{
  return new Door(*this);
}

bool Door::get_is_blocking() const
{
  // Only closed doors are blocking.
  return (state.get_state() == EntranceStateType::ENTRANCE_TYPE_CLOSED);
}

// Doors/gates/etc work a little differently because they need to generate
// their symbol based on their current state, rather than a permanent
// value.
//
// JCD SYMBOL SPRITESHEET FIXME
Symbol Door::get_symbol() const
{
  Symbol s = state.get_symbol();
  s.set_colour(get_colour());

  return s;
}

string Door::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_DOOR;
}

ClassIdentifier Door::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DOOR;
}
