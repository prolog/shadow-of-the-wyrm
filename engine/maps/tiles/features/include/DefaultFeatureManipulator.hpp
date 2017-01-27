#pragma once
#include "IFeatureManipulator.hpp"

class DefaultFeatureManipulator : public IFeatureManipulator
{
  public:
    DefaultFeatureManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;
};

