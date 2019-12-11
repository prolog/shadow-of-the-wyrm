#include "Tannery.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Tannery::Tannery(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TANNERY, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Tannery::clone()
{
  return new Tannery(*this);
}

ClassIdentifier Tannery::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TANNERY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tannery_test.cpp"
#endif

