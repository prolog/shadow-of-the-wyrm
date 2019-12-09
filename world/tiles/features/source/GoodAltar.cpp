#include "GoodAltar.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

// This constructor is only used by the serialization code.
GoodAltar::GoodAltar(const Symbol& new_symbol)
: Altar(new_symbol, "", MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_GOOD)
{
}

GoodAltar::GoodAltar(const Symbol& new_symbol, const std::string& new_deity_id)
: Altar(new_symbol, new_deity_id, MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_GOOD)
{
}

Feature* GoodAltar::clone()
{
  return new GoodAltar(*this);
}

string GoodAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GOOD_ALTAR;
}

ClassIdentifier GoodAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GOOD_ALTAR;
}