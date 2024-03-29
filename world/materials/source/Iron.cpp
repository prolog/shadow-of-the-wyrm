#include "Iron.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Iron::get_type() const
{
  return MaterialType::MATERIAL_TYPE_IRON;
}

string Iron::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_IRON;
}

bool Iron::get_is_flammable() const
{
  return false;
}

bool Iron::get_is_explosive() const
{
  return false;
}

bool Iron::get_is_corrodible() const
{
  return false;
}

bool Iron::get_crumbles() const
{
  return false;
}

Material* Iron::clone()
{
  return new Iron(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Iron_test.cpp"
#endif
