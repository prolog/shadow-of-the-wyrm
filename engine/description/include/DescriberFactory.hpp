#pragma once
#include "IDescriber.hpp"
#include "Tile.hpp"
#include "Creature.hpp"

class DescriberFactory
{
  public:
    static IDescriberPtr create_describer(TilePtr tile);
    static IDescriberPtr create_describer(CreaturePtr creature);
    static IDescriberPtr create_describer(FeaturePtr feature);
    static IDescriberPtr create_describer(const Inventory& inv);

  protected:
    DescriberFactory();
    ~DescriberFactory();
};
