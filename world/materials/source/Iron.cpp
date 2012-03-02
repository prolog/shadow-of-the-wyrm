#include "Iron.hpp"
#include "StringConstants.hpp"

using namespace std;

MaterialType Iron::get_type() const
{
  return MATERIAL_TYPE_IRON;
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

bool Iron::get_can_rust() const
{
  return true;
}

Material* Iron::clone()
{
  return new Iron(*this);
}
