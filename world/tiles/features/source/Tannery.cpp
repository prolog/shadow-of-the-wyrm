#include "Tannery.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Tannery::Tannery()
: Feature(MATERIAL_TYPE_WOOD, ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* Tannery::clone()
{
  return new Tannery(*this);
}

uchar Tannery::get_symbol() const
{
  return '^';
}

string Tannery::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TANNERY;
}

ClassIdentifier Tannery::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TANNERY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tannery_test.cpp"
#endif

