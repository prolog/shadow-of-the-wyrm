#include "Stone.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Stone::get_type() const
{
  return MaterialType::MATERIAL_TYPE_STONE;
}

string Stone::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_STONE;
}

bool Stone::get_is_flammable() const
{
  return false;
}

bool Stone::get_is_explosive() const
{
  return false;
}

bool Stone::get_is_corrodible() const
{
  return false;
}

bool Stone::get_crumbles() const
{
  return true;
}

Material* Stone::clone()
{
  return new Stone(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Stone_test.cpp"
#endif
