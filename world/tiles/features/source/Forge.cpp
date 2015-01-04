#include "Forge.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Forge::Forge()
: Feature(MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* Forge::clone()
{
  return new Forge(*this);
}

uchar Forge::get_symbol() const
{
  return '&';
}

string Forge::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FORGE;
}

ClassIdentifier Forge::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FORGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Forge_test.cpp"
#endif

