#pragma once
#include "IFeatureManipulator.hpp"

class EvilAltarManipulator : public IFeatureManipulator
{
  public:
    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature);
};

