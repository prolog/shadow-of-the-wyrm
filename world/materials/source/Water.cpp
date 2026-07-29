#include "MaterialTextKeys.hpp"
#include "Water.hpp"

using namespace std;

MaterialType Water::get_type() const
{
  return MaterialType::MATERIAL_TYPE_WATER;
}

string Water::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_WATER;
}

bool Water::get_is_flammable() const
{
  return false;
}

bool Water::get_is_explosive() const
{
  return false;
}

bool Water::get_is_corrodible() const
{
  return false;
}

bool Water::get_crumbles() const
{
  return false;
}

Colour Water::get_colour() const
{
  return Colour::COLOUR_BOLD_WHITE;
}

Material* Water::clone()
{
  return new Water(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Water_test.cpp"
#endif