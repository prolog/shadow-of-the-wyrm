#include "Glass.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Glass::get_type() const
{
  return MaterialType::MATERIAL_TYPE_GLASS;
}

string Glass::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_GLASS;
}

bool Glass::get_is_flammable() const
{
  return false;
}

bool Glass::get_is_explosive() const
{
  return true;
}

bool Glass::get_is_corrodible() const
{
  return false; // Yeah, yeah, I know.
}

bool Glass::get_crumbles() const
{
  return false;
}

Material* Glass::clone()
{
  return new Glass(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Glass_test.cpp"
#endif
