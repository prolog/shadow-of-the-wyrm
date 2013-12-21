#include "Gate.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Gate::Gate()
{
}

Feature* Gate::clone()
{
  return new Gate(*this);
}

// Gates are always made of iron
Gate::Gate(LockPtr new_lock, const EntranceState& new_state)
: Entrance(new_lock, new_state)
{
  set_material_type(MATERIAL_TYPE_IRON);
}

bool Gate::handle(std::shared_ptr<Tile>, std::shared_ptr<Creature>)
{
  // JCD FIXME;
  return true;
}

bool Gate::kick()
{
  // JCD FIXME: Gates can't be kicked open.
  return false;
}

bool Gate::get_is_blocking() const
{
  return (state.get_state() == ENTRANCE_TYPE_CLOSED);
}

uchar Gate::get_symbol() const
{
  return state.get_symbol();
}

string Gate::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GATE;
}

ClassIdentifier Gate::internal_class_identifier() const
{
  return CLASS_ID_GATE;
}