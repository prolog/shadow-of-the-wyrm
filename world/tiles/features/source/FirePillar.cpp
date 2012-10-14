#include "FirePillar.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

FirePillar::FirePillar()
: Feature(MaterialFactory::create_material(MATERIAL_TYPE_STONE))
{
}

bool FirePillar::handle()
{
  return true;
}

bool FirePillar::kick()
{
  return true;
}

bool FirePillar::get_is_blocking() const
{
  return true;
}

uchar FirePillar::get_symbol() const
{
  return 'Y';
}

string FirePillar::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FIRE_PILLAR;
}

ClassIdentifier FirePillar::internal_class_identifier() const
{
  return CLASS_ID_FIRE_PILLAR;
}
// FIXME: Still need to add lit/unlit state.
