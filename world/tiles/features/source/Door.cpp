#include "Door.hpp"
#include "FeatureDescriptionTextKeys.hpp"

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
  return ClassIdentifier::CLASS_ID_DOOR;
}
