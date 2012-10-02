#include "NeutralAltar.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

// This constructor is only used by the serialization code
NeutralAltar::NeutralAltar()
: Altar("", MaterialFactory::create_material(MATERIAL_TYPE_STONE))
{
}

NeutralAltar::NeutralAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_STONE))
{
}

string NeutralAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR;
}
