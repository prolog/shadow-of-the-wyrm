#include "NeutralAltar.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

// This constructor is only used by the serialization code
NeutralAltar::NeutralAltar()
: Altar("", MATERIAL_TYPE_STONE)
{
}

NeutralAltar::NeutralAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MATERIAL_TYPE_STONE)
{
}

Feature* NeutralAltar::clone()
{
  return new NeutralAltar(*this);
}

string NeutralAltar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR;
}

ClassIdentifier NeutralAltar::internal_class_identifier() const
{
  return CLASS_ID_NEUTRAL_ALTAR;
}