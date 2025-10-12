#pragma once
#include "DefaultFeatureManipulator.hpp"
#include "Feature.hpp"

class CauldronManipulator : public DefaultFeatureManipulator
{
  public:
    CauldronManipulator(FeaturePtr feature);

    void strike(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

