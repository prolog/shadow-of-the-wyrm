#include "Bone.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Bone::get_type() const
{
  return MaterialType::MATERIAL_TYPE_BONE;
}

string Bone::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_BONE;
}

bool Bone::get_is_flammable() const
{
  return false;
}

bool Bone::get_is_explosive() const
{
  return false;
}

bool Bone::get_is_corrodible() const
{
  return true;
}

bool Bone::get_crumbles() const
{
  return false;
}

Colour Bone::get_colour() const
{
  return Colour::COLOUR_BOLD_WHITE;
}

Material* Bone::clone()
{
  return new Bone(*this);
}

#ifdef UNIT_TESTS
#include "unit_tests/Bone_test.cpp"
#endif
