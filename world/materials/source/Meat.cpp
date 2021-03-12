#include "MaterialTextKeys.hpp"
#include "Meat.hpp"

using namespace std;

MaterialType Meat::get_type() const
{
  return MaterialType::MATERIAL_TYPE_MEAT;
}

string Meat::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_MEAT;
}

bool Meat::get_is_flammable() const
{
  return true;
}

bool Meat::get_is_explosive() const
{
  return false;
}

bool Meat::get_is_corrodible() const
{
  return true;
}

bool Meat::get_crumbles() const
{
  return false;
}

Colour Meat::get_colour() const
{
  return Colour::COLOUR_WHITE;
}

Material* Meat::clone()
{
  return new Meat(*this);
}
