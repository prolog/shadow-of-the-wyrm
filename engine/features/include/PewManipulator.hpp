#pragma once
#include "IFeatureManipulator.hpp"

class PewManipulator : public IFeatureManipulator
{
  public:
    PewManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

