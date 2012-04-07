#include "GoodAltar.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

GoodAltar::GoodAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_MARBLE))
{
}

string GoodAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GOOD_ALTAR;
}
