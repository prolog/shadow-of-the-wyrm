#include "Leather.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Leather::get_type() const
{
  return MaterialType::MATERIAL_TYPE_LEATHER;
}

string Leather::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_LEATHER;
}

bool Leather::get_is_flammable() const
{
  return false;
}

bool Leather::get_is_explosive() const
{
  return false;
}

bool Leather::get_is_corrodible() const
{
  return false;
}

bool Leather::get_crumbles() const
{
  return false;
}

Colour Leather::get_colour() const
{
  return Colour::COLOUR_YELLOW;
}

Material* Leather::clone()
{
  return new Leather(*this);
}

bool Leather::get_material_floats() const
{
  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Leather_test.cpp"
#endif