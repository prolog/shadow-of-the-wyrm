#pragma once
#include "IFeatureManipulator.hpp"

class TrapManipulator : public IFeatureManipulator
{
  public:
    TrapManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

