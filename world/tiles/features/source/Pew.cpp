#include "MaterialFactory.hpp"
#include "Pew.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Pew::Pew(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PEW, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Pew::clone()
{
  return new Pew(*this);
}

float Pew::get_piety_loss_multiplier() const
{
  return 0.5f;
}

ClassIdentifier Pew::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PEW;
}

#ifdef UNIT_TESTS
#include "unit_tests/Pew_test.cpp"
#endif

