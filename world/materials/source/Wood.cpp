#include "MaterialTextKeys.hpp"
#include "Wood.hpp"

using namespace std;

MaterialType Wood::get_type() const
{
  return MaterialType::MATERIAL_TYPE_WOOD;
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

bool Wood::get_crumbles() const
{
  return false;
}

Colour Wood::get_colour() const
{
  return Colour::COLOUR_YELLOW;
}

Material* Wood::clone()
{
  return new Wood(*this);
}

bool Wood::get_material_floats() const
{
  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Wood_test.cpp"
#endif