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

IDescriberPtr DescriberFactory::create_describer(CreaturePtr viewing_creature, TilePtr tile, const bool is_world_map)
{
  IDescriberPtr describer = std::make_unique<TileDescriber>(viewing_creature, tile, is_world_map);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr viewing_creature, CreaturePtr creature)
{
  IDescriberPtr describer = std::make_unique<CreatureDescriber>(viewing_creature, creature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(FeaturePtr feature)
{
  IDescriberPtr describer = std::make_unique<FeatureDescriber>(feature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(const bool blind, const IInventoryPtr inv)
{
  IDescriberPtr describer = std::make_unique<InventoryDescriber>(blind, inv);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr creature, const Spell& spell)
{
  IDescriberPtr describer = std::make_unique<SpellDescriber>(creature, spell);
  return describer;
}