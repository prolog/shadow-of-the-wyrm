#include "Gate.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Gate::Gate(const Symbol& new_symbol)
: Entrance(new_symbol)
{
}

Feature* Gate::clone()
{
  return new Gate(*this);
}

// Gates are always made of iron
Gate::Gate(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state)
: Entrance(new_symbol, new_lock, new_state)
{
  set_material_type(MaterialType::MATERIAL_TYPE_IRON);
}

bool Gate::get_is_blocking() const
{
  return (state.get_state() == EntranceStateType::ENTRANCE_TYPE_CLOSED);
}

// JCD SYMBOL SPRITESHEET FIXME
Symbol Gate::get_symbol() const
{
  Symbol s = state.get_symbol();
  s.set_colour(get_colour());

  return s;
}

string Gate::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GATE;
}

ClassIdentifier Gate::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GATE;
}
