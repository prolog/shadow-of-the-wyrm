#include "MaterialFactory.hpp"
#include "Pew.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Pew::Pew()
: Feature(MATERIAL_TYPE_WOOD, ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* Pew::clone()
{
  return new Pew(*this);
}

uchar Pew::get_symbol() const
{
  return '-';
}

string Pew::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PEW;
}

float Pew::get_piety_loss_multiplier() const
{
  return 0.5f;
}

ClassIdentifier Pew::internal_class_identifier() const
{
  return CLASS_ID_PEW;
}

#ifdef UNIT_TESTS
#include "unit_tests/Pew_test.cpp"
#endif

