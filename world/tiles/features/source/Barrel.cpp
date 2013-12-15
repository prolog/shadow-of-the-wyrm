#include "Barrel.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Barrel::Barrel()
: Feature(MATERIAL_TYPE_WOOD)
{
}

Feature* Barrel::clone()
{
  return new Barrel(*this);
}

bool Barrel::handle()
{
  return true;
}

bool Barrel::kick()
{
  return true;
}

uchar Barrel::get_symbol() const
{
  return 'o';
}

string Barrel::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BARREL;
}

ClassIdentifier Barrel::internal_class_identifier() const
{
  return CLASS_ID_BARREL;
}

#ifdef UNIT_TESTS
#include "unit_tests/Barrel_test.cpp"
#endif

