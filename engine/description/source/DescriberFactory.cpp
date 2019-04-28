#include "CreatureDescriber.hpp"
#include "DescriberFactory.hpp"
#include "FeatureDescriber.hpp"
#include "InventoryDescriber.hpp"
#include "SpellDescriber.hpp"
#include "TileDescriber.hpp"

DescriberFactory::DescriberFactory()
{
}

DescriberFactory::~DescriberFactory()
{
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr viewing_creature, TilePtr tile)
{
  IDescriberPtr describer = std::make_shared<TileDescriber>(viewing_creature, tile);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr viewing_creature, CreaturePtr creature)
{
  IDescriberPtr describer = std::make_shared<CreatureDescriber>(viewing_creature, creature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(FeaturePtr feature)
{
  IDescriberPtr describer = std::make_shared<FeatureDescriber>(feature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(const bool blind, const IInventoryPtr inv)
{
  IDescriberPtr describer = std::make_shared<InventoryDescriber>(blind, inv);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr creature, const Spell& spell)
{
  IDescriberPtr describer = std::make_shared<SpellDescriber>(creature, spell);
  return describer;
}