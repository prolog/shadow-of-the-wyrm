#include "StoneMarker.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

StoneMarker::StoneMarker()
: Feature(MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* StoneMarker::clone()
{
  return new StoneMarker(*this);
}

uchar StoneMarker::get_symbol() const
{
  return '+';
}

float StoneMarker::get_hp_regeneration_multiplier() const
{
  return 1.0f;
}

float StoneMarker::get_ap_regeneration_multiplier() const
{
  return 0.1f;
}

string StoneMarker::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_STONE_MARKER;
}

ClassIdentifier StoneMarker::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STONE_MARKER;
}

#ifdef UNIT_TESTS
#include "unit_tests/StoneMarker_test.cpp"
#endif

