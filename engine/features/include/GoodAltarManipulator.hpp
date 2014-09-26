#pragma once
#include "IFeatureManipulator.hpp"

class GoodAltarManipulator : public IFeatureManipulator
{
  public:
    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature);
};

