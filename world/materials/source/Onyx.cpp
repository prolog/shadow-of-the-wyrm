#include "Onyx.hpp"
#include "StringConstants.hpp"

using namespace std;

MaterialType Onyx::get_type() const
{
  return MATERIAL_TYPE_ONYX;
}

string Onyx::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_ONYX;
}

bool Onyx::get_is_flammable() const
{
  return false;
}

bool Onyx::get_is_explosive() const
{
  return false;
}

bool Onyx::get_is_corrodible() const
{
  return false;
}

bool Onyx::get_can_rust() const
{
  return false;
}

Colour Onyx::get_colour() const
{
  return COLOUR_BOLD_BLACK;
}

Material* Onyx::clone()
{
  return new Onyx(*this);
}

