#include "Gate.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Gate::Gate(const Symbol& new_symbol)
: Entrance(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GATE, new_symbol)
{
}

// Gates are always made of iron
Gate::Gate(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state)
: Entrance(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GATE, new_symbol, new_lock, new_state)
{
  set_material_type(MaterialType::MATERIAL_TYPE_IRON);
}

Feature* Gate::clone()
{
  return new Gate(*this);
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

ClassIdentifier Gate::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GATE;
}
