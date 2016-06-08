#pragma once
#include "ActionManager.hpp"
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class SarcophagusManipulator : public IFeatureManipulator
{
  public:
    SarcophagusManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
};

