#include "Cloth.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Cloth::get_type() const
{
  return MATERIAL_TYPE_CLOTH;
}

string Cloth::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_CLOTH;
}

bool Cloth::get_is_flammable() const
{
  return true;
}

bool Cloth::get_is_explosive() const
{
  return false;
}

bool Cloth::get_is_corrodible() const
{
  return true;
}

bool Cloth::get_can_rust() const
{
  return false;
}

Colour Cloth::get_colour() const
{
  return Colour::COLOUR_GREEN;
}

Material* Cloth::clone()
{
  return new Cloth(*this);
}

