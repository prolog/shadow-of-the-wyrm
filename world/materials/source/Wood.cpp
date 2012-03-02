#include "StringConstants.hpp"
#include "Wood.hpp"

using namespace std;

MaterialType Wood::get_type() const
{
  return MATERIAL_TYPE_WOOD;
}

string Wood::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_WOOD;
}

bool Wood::get_is_flammable() const
{
  return true;
}

bool Wood::get_is_explosive() const
{
  return false;
}

bool Wood::get_is_corrodible() const
{
  return true;
}

bool Wood::get_can_rust() const
{
  return false;
}

Colour Wood::get_colour() const
{
  return COLOUR_YELLOW;
}

Material* Wood::clone()
{
  return new Wood(*this);
}
