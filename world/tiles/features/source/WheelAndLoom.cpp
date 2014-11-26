#include "WheelAndLoom.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

WheelAndLoom::WheelAndLoom()
: Feature(MATERIAL_TYPE_WOOD, ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* WheelAndLoom::clone()
{
  return new WheelAndLoom(*this);
}

uchar WheelAndLoom::get_symbol() const
{
  return '^';
}

string WheelAndLoom::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WHEEL_AND_LOOM;
}

ClassIdentifier WheelAndLoom::internal_class_identifier() const
{
  return CLASS_ID_WHEEL_AND_LOOM;
}

#ifdef UNIT_TESTS
#include "unit_tests/WheelAndLoom_test.cpp"
#endif

