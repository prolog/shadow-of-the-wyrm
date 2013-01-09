#include "EvilAltar.hpp"
#include "StringConstants.hpp"

using std::string;

EvilAltar::EvilAltar()
: Altar("", MATERIAL_TYPE_ONYX)
{
}

EvilAltar::EvilAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MATERIAL_TYPE_ONYX)
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
  return CLASS_ID_EVIL_ALTAR;
}