#include "Fountain.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

Fountain::Fountain(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FOUNTAIN, MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Fountain::clone()
{
  return new Fountain(*this);
}

ClassIdentifier Fountain::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FOUNTAIN;
}

#ifdef UNIT_TESTS
#include "unit_tests/Fountain_test.cpp"
#endif

