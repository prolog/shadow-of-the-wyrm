#include "Paper.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Paper::get_type() const
{
  return MaterialType::MATERIAL_TYPE_PAPER;
}

string Paper::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_PAPER;
}

bool Paper::get_is_flammable() const
{
  return true;
}

bool Paper::get_is_explosive() const
{
  return false;
}

bool Paper::get_is_corrodible() const
{
  return true;
}

bool Paper::get_can_rust() const
{
  return false;
}

Colour Paper::get_colour() const
{
  return Colour::COLOUR_BOLD_WHITE;
}

Material* Paper::clone()
{
  return new Paper(*this);
}
