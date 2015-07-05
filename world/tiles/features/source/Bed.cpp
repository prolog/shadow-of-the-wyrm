#include "Bed.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Bed::Bed()
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* Bed::clone()
{
  return new Bed(*this);
}

uchar Bed::get_symbol() const
{
  return '~';
}

float Bed::get_hp_regeneration_multiplier() const
{
  return 0.3f;
}

float Bed::get_ap_regeneration_multiplier() const
{
  return 0.75f;
}

string Bed::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BED;
}

ClassIdentifier Bed::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BED;
}

#ifdef UNIT_TESTS
#include "unit_tests/Bed_test.cpp"
#endif

