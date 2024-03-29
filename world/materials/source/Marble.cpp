#include "Marble.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Marble::get_type() const
{
  return MaterialType::MATERIAL_TYPE_MARBLE;
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

bool Marble::get_crumbles() const
{
  return true;
}

Colour Marble::get_colour() const
{
  return Colour::COLOUR_BOLD_WHITE;
}

Material* Marble::clone()
{
  return new Marble(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Marble_test.cpp"
#endif
