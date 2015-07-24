#pragma once
#include "AltarManipulator.hpp"

class GoodAltarManipulator : public AltarManipulator
{
  public:
    GoodAltarManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
};

