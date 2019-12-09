#include "Fountain.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Fountain::Fountain(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Fountain::clone()
{
  return new Fountain(*this);
}

string Fountain::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FOUNTAIN;
}

ClassIdentifier Fountain::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FOUNTAIN;
}

#ifdef UNIT_TESTS
#include "unit_tests/Fountain_test.cpp"
#endif

