#include "Table.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Table::Table(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TABLE, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Table::clone()
{
  return new Table(*this);
}

ClassIdentifier Table::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TABLE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Table_test.cpp"
#endif

