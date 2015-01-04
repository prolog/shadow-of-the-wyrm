#include "Steel.hpp"
#include "MaterialTextKeys.hpp"

using namespace std;

MaterialType Steel::get_type() const
{
  return MaterialType::MATERIAL_TYPE_STEEL;
}

string Steel::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_STEEL;
}

bool Steel::get_is_flammable() const
{
  return false;
}

bool Steel::get_is_explosive() const
{
  return false;
}

bool Steel::get_is_corrodible() const
{
  return false;
}

bool Steel::get_can_rust() const
{
  return false;
}

Material* Steel::clone()
{
  return new Steel(*this);
}

