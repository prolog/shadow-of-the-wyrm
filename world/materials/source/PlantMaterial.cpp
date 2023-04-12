#include "MaterialTextKeys.hpp"
#include "PlantMaterial.hpp"

using namespace std;

MaterialType PlantMaterial::get_type() const
{
  return MaterialType::MATERIAL_TYPE_PLANT;
}

string PlantMaterial::get_name_sid() const
{
  return MaterialTextKeys::MATERIAL_PLANT;
}

bool PlantMaterial::get_is_flammable() const
{
  return true;
}

bool PlantMaterial::get_is_explosive() const
{
  return false;
}

bool PlantMaterial::get_is_corrodible() const
{
  return true;
}

bool PlantMaterial::get_crumbles() const
{
  return false;
}

Colour PlantMaterial::get_colour() const
{
  return Colour::COLOUR_BOLD_GREEN;
}

Material* PlantMaterial::clone()
{
  return new PlantMaterial(*this);
}

bool PlantMaterial::get_material_floats() const
{
  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/PlantMaterial_test.cpp"
#endif
