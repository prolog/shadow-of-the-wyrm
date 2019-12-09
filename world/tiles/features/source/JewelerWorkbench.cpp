#include "JewelerWorkbench.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

JewelerWorkbench::JewelerWorkbench(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* JewelerWorkbench::clone()
{
  return new JewelerWorkbench(*this);
}

string JewelerWorkbench::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_JEWELER_WORKBENCH;
}

ClassIdentifier JewelerWorkbench::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH;
}

#ifdef UNIT_TESTS
#include "unit_tests/JewelerWorkbench_test.cpp"
#endif

