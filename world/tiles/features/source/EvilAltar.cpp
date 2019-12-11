#include "EvilAltar.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

EvilAltar::EvilAltar(const Symbol& new_symbol)
: Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR, new_symbol, "", MaterialType::MATERIAL_TYPE_ONYX, AlignmentRange::ALIGNMENT_RANGE_EVIL)
{
}

EvilAltar::EvilAltar(const Symbol& new_symbol, const std::string& new_deity_id)
: Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR, new_symbol, new_deity_id, MaterialType::MATERIAL_TYPE_ONYX, AlignmentRange::ALIGNMENT_RANGE_EVIL)
{
}

Feature* EvilAltar::clone()
{
  return new EvilAltar(*this);
}

ClassIdentifier EvilAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EVIL_ALTAR;
}