#pragma once
#include "DefaultFeatureManipulator.hpp"
#include "Feature.hpp"

class CauldronManipulator : public DefaultFeatureManipulator
{
  public:
    CauldronManipulator(FeaturePtr feature);

    void strike(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature, ItemPtr item) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    void add_nothing_brewable_message(CreaturePtr creature);
};

