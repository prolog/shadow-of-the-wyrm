#include "NeutralAltar.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

// This constructor is only used by the serialization code
NeutralAltar::NeutralAltar(const Symbol& new_symbol)
: Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR, new_symbol, "", MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

NeutralAltar::NeutralAltar(const Symbol& new_symbol, const std::string& new_deity_id)
: Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR, new_symbol, new_deity_id, MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* NeutralAltar::clone()
{
  return new NeutralAltar(*this);
}

ClassIdentifier NeutralAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR;
}