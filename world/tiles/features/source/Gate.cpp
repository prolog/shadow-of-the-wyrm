#include "Gate.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

Gate::Gate()
{
}

// Gates are always made of iron
Gate::Gate(LockPtr new_lock, const EntranceState& new_state)
: Entrance(new_lock, new_state)
{
  MaterialPtr iron = MaterialFactory::create_material(MATERIAL_TYPE_IRON);
  set_material(iron);
}

bool Gate::handle()
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


