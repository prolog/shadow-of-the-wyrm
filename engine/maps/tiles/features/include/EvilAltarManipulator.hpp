#pragma once
#include "AltarManipulator.hpp"

class EvilAltarManipulator : public AltarManipulator
{
  public:
    EvilAltarManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
};

