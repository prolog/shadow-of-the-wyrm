#pragma once
#include "IFeatureManipulator.hpp"

class DefaultFeatureManipulator : public IFeatureManipulator
{
  public:
    DefaultFeatureManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

