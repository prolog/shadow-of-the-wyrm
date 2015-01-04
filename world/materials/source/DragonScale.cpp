#include "DragonScale.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType DragonScale::get_type() const
{
  return MaterialType::MATERIAL_TYPE_DRAGON_SCALE;
}

string DragonScale::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_DRAGON_SCALE;
}

bool DragonScale::get_is_flammable() const
{
  return false;
}

bool DragonScale::get_is_explosive() const
{
  return false;
}

bool DragonScale::get_is_corrodible() const
{
  return false;
}

bool DragonScale::get_can_rust() const
{
  return false;
}

Colour DragonScale::get_colour() const
{
  return Colour::COLOUR_BOLD_RED;
}

Material* DragonScale::clone()
{
  return new DragonScale(*this);
}

