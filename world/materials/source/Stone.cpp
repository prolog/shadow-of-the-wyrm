#include "Stone.hpp"
#include "StringConstants.hpp"

using namespace std;

MaterialType Stone::get_type() const
{
  return MATERIAL_TYPE_STONE;
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

bool Stone::get_can_rust() const
{
  return false;
}

Material* Stone::clone()
{
  return new Stone(*this);
}
