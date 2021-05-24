#pragma once
#include "ActionManager.hpp"
#include "FeatureManipulator.hpp"

class KilnManipulator : public FeatureManipulator
{
  public:
    KilnManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    bool check_for_clay(CreaturePtr creature);
};

