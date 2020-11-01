#include "Gases.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Gases::get_type() const
{
  return MaterialType::MATERIAL_TYPE_GASES;
}

string Gases::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_GASES;
}

bool Gases::get_is_flammable() const
{
  return true;
}

bool Gases::get_is_explosive() const
{
  return true;
}

bool Gases::get_is_corrodible() const
{
  return false;
}

bool Gases::get_crumbles() const
{
  return false;
}

Colour Gases::get_colour() const
{
  return Colour::COLOUR_WHITE;
}

Material* Gases::clone()
{
  return new Gases(*this);
}

