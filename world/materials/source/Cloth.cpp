#include "Cloth.hpp"
#include "StringConstants.hpp"

using namespace std;

MaterialType Cloth::get_type() const
{
  return MATERIAL_TYPE_CLOTH;
}

string Cloth::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_CLOTH;
}

bool Cloth::get_is_flammable() const
{
  return true;
}

bool Cloth::get_is_explosive() const
{
  return false;
}

bool Cloth::get_is_corrodible() const
{
  return true;
}

bool Cloth::get_can_rust() const
{
  return false;
}

Colour Cloth::get_colour() const
{
  return COLOUR_GREEN;
}

Material* Cloth::clone()
{
  return new Cloth(*this);
}

ClassIdentifier Cloth::internal_class_identifier() const
{
  return CLASS_ID_CLOTH;
}