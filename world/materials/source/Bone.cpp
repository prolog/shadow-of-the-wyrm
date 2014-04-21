#include "Bone.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Bone::get_type() const
{
  return MATERIAL_TYPE_BONE;
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

bool Bone::get_can_rust() const
{
  return false;
}

Colour Bone::get_colour() const
{
  return COLOUR_BOLD_WHITE;
}

Material* Bone::clone()
{
  return new Bone(*this);
}

