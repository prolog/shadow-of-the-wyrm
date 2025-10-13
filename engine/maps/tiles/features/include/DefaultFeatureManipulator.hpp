#pragma once
#include "FeatureManipulator.hpp"

class DefaultFeatureManipulator : public FeatureManipulator
{
  public:
    DefaultFeatureManipulator(FeaturePtr feature);

    void strike(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature, ItemPtr item) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;
};

