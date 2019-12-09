#include "WheelAndLoom.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

WheelAndLoom::WheelAndLoom(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* WheelAndLoom::clone()
{
  return new WheelAndLoom(*this);
}

string WheelAndLoom::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WHEEL_AND_LOOM;
}

ClassIdentifier WheelAndLoom::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM;
}

#ifdef UNIT_TESTS
#include "unit_tests/WheelAndLoom_test.cpp"
#endif

