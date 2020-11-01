#include "UnknownMaterial.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType UnknownMaterial::get_type() const
{
  return MaterialType::MATERIAL_TYPE_UNKNOWN;
}

string UnknownMaterial::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_UNKNOWN;
}

bool UnknownMaterial::get_is_flammable() const
{
  return false;
}

bool UnknownMaterial::get_is_explosive() const
{
  return false;
}

bool UnknownMaterial::get_is_corrodible() const
{
  return false;
}

bool UnknownMaterial::get_crumbles() const
{
  return false;
}

Colour UnknownMaterial::get_colour() const
{
  return Colour::COLOUR_BOLD_YELLOW;
}

Material* UnknownMaterial::clone()
{
  return new UnknownMaterial(*this);
}

