#include "EvilAltar.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

EvilAltar::EvilAltar()
: Altar("", MaterialFactory::create_material(MATERIAL_TYPE_ONYX))
{
}

EvilAltar::EvilAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_ONYX))
{
}

string EvilAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR;
}

ClassIdentifier EvilAltar::internal_class_identifier() const
{
  return CLASS_ID_EVIL_ALTAR;
}