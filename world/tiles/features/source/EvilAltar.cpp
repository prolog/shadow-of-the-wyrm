#include "EvilAltar.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

EvilAltar::EvilAltar()
: Altar("", MaterialType::MATERIAL_TYPE_ONYX, AlignmentRange::ALIGNMENT_RANGE_EVIL)
{
}

EvilAltar::EvilAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialType::MATERIAL_TYPE_ONYX, AlignmentRange::ALIGNMENT_RANGE_EVIL)
{
}

Feature* EvilAltar::clone()
{
  return new EvilAltar(*this);
}

string EvilAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR;
}

ClassIdentifier EvilAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EVIL_ALTAR;
}