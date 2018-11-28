#include "Pulper.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Pulper::Pulper()
: Feature(MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* Pulper::clone()
{
  return new Pulper(*this);
}

uchar Pulper::get_symbol() const
{
  return ':';
}

string Pulper::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PULPER;
}

ClassIdentifier Pulper::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PULPER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Pulper_test.cpp"
#endif

