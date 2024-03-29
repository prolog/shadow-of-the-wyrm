#include "Gold.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Gold::get_type() const
{
  return MaterialType::MATERIAL_TYPE_GOLD;
}

string Gold::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_GOLD;
}

bool Gold::get_is_flammable() const
{
  return false;
}

bool Gold::get_is_explosive() const
{
  return false;
}

bool Gold::get_is_corrodible() const
{
  return false;
}

bool Gold::get_crumbles() const
{
  return false;
}

Colour Gold::get_colour() const
{
  return Colour::COLOUR_BOLD_YELLOW;
}

Material* Gold::clone()
{
  return new Gold(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Gold_test.cpp"
#endif

