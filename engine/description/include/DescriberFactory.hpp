#pragma once
#include "IDescriber.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "Spell.hpp"

class DescriberFactory
{
  public:
    static IDescriberPtr create_describer(TilePtr tile);
    static IDescriberPtr create_describer(CreaturePtr creature);
    static IDescriberPtr create_describer(FeaturePtr feature);
    static IDescriberPtr create_describer(const bool blind, const Inventory& inv);
    static IDescriberPtr create_describer(CreaturePtr creature, const Spell& spell);

  protected:
    DescriberFactory();
    ~DescriberFactory();
};
