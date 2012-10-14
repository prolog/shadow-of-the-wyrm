#include "GoodAltar.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

// This constructor is only used by the serialization code.
GoodAltar::GoodAltar()
: Altar("", MaterialFactory::create_material(MATERIAL_TYPE_MARBLE))
{
}

GoodAltar::GoodAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_MARBLE))
{
}

string GoodAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GOOD_ALTAR;
}

ClassIdentifier GoodAltar::internal_class_identifier() const
{
  return CLASS_ID_GOOD_ALTAR;
}