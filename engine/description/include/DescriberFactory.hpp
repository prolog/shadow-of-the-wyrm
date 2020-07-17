#pragma once
#include "IDescriber.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "Spell.hpp"

class DescriberFactory
{
  public:
    static IDescriberPtr create_describer(CreaturePtr viewing_creature, TilePtr tile, const bool is_world_map);
    static IDescriberPtr create_describer(CreaturePtr viewing_creature, CreaturePtr creature);
    static IDescriberPtr create_describer(FeaturePtr feature);
    static IDescriberPtr create_describer(const bool blind, const IInventoryPtr inv);
    static IDescriberPtr create_describer(CreaturePtr creature, const Spell& spell);

  protected:
    DescriberFactory();
    ~DescriberFactory();
};
