#include "Ivory.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Ivory::get_type() const
{
  return MaterialType::MATERIAL_TYPE_IVORY;
}

string Ivory::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_IVORY;
}

bool Ivory::get_is_flammable() const
{
  return false;
}

bool Ivory::get_is_explosive() const
{
  return false;
}

bool Ivory::get_is_corrodible() const
{
  return false;
}

bool Ivory::get_crumbles() const
{
  return false;
}

Colour Ivory::get_colour() const
{
  return Colour::COLOUR_BOLD_WHITE;
}

Material* Ivory::clone()
{
  return new Ivory(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Ivory_test.cpp"
#endif
