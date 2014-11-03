#pragma once
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class ForgeManipulator : public IFeatureManipulator
{
  public:
    ForgeManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

