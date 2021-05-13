#include "Clay.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Clay::get_type() const
{
  return MaterialType::MATERIAL_TYPE_CLAY;
}

string Clay::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_CLAY;
}

bool Clay::get_is_flammable() const
{
  return false;
}

bool Clay::get_is_explosive() const
{
  return false;
}

bool Clay::get_is_corrodible() const
{
  return false;
}

bool Clay::get_crumbles() const
{
  return true;
}

Colour Clay::get_colour() const
{
  return Colour::COLOUR_RED;
}

Material* Clay::clone()
{
  return new Clay(*this);
}

bool Clay::get_material_floats() const
{
  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/Clay_test.cpp"
#endif