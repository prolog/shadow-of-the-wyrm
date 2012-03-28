#include "MaterialFactory.hpp"
#include "Pew.hpp"

Pew::Pew()
: Feature(MaterialFactory::create_material(MATERIAL_TYPE_WOOD))
{
}

// Sit or stand, depending on the creature's current state.
bool Pew::handle()
{
  return true;
}

// Destroy the pew.
bool Pew::kick()
{
  return true;
}

uchar Pew::get_symbol() const
{
  return '-';
}
