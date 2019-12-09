#include "Pulper.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Pulper::Pulper(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Pulper::clone()
{
  return new Pulper(*this);
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

