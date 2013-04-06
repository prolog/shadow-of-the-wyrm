#include "Marble.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Marble::get_type() const
{
  return MATERIAL_TYPE_MARBLE;
}

string Marble::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_MARBLE;
}

bool Marble::get_is_flammable() const
{
  return false;
}

bool Marble::get_is_explosive() const
{
  return false;
}

bool Marble::get_is_corrodible() const
{
  return false;
}

bool Marble::get_can_rust() const
{
  return false;
}

Colour Marble::get_colour() const
{
  return COLOUR_BOLD_WHITE;
}

Material* Marble::clone()
{
  return new Marble(*this);
}

