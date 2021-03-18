#include "Material.hpp"

using namespace std;

Colour Material::get_colour() const
{
  return Colour::COLOUR_WHITE;
}

bool Material::get_material_floats() const
{
  return false; // most things don't
}