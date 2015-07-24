#pragma once
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class BarrelManipulator : public IFeatureManipulator
{
  public:
    BarrelManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

