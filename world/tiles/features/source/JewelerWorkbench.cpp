#include "JewelerWorkbench.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

JewelerWorkbench::JewelerWorkbench()
: Feature(MATERIAL_TYPE_WOOD, ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* JewelerWorkbench::clone()
{
  return new JewelerWorkbench(*this);
}

uchar JewelerWorkbench::get_symbol() const
{
  return '&';
}

string JewelerWorkbench::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_JEWELER_WORKBENCH;
}

ClassIdentifier JewelerWorkbench::internal_class_identifier() const
{
  return CLASS_ID_JEWELER_WORKBENCH;
}

#ifdef UNIT_TESTS
#include "unit_tests/JewelerWorkbench_test.cpp"
#endif

