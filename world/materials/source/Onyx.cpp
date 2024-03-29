#include "Onyx.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Onyx::get_type() const
{
  return MaterialType::MATERIAL_TYPE_ONYX;
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

bool Onyx::get_crumbles() const
{
  return true;
}

Colour Onyx::get_colour() const
{
  return Colour::COLOUR_BOLD_BLACK;
}

Material* Onyx::clone()
{
  return new Onyx(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Onyx_test.cpp"
#endif
