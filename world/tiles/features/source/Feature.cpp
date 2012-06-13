#include "Feature.hpp"

Feature::Feature(MaterialPtr new_material)
: material(new_material)
{
}

void Feature::set_trap(TrapPtr new_trap)
{
  trap = new_trap;
}

TrapPtr Feature::get_trap()
{
  return trap;
}

void Feature::set_material(MaterialPtr new_material)
{
  material = new_material;
}

MaterialPtr Feature::get_material()
{
  return material;
}

// By default, Features are not blocking.
bool Feature::get_is_blocking() const
{
  return false;
}

// Use the material's colour
Colour Feature::get_colour() const
{
  Colour colour = COLOUR_WHITE;
  
  if (material)
  {
    colour = material->get_colour();
  }
  
  return colour;
}
