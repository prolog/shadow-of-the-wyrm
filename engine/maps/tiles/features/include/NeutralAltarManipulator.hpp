#pragma once
#include "AltarManipulator.hpp"

class NeutralAltarManipulator : public AltarManipulator
{
  public:
    NeutralAltarManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
};

