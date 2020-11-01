#pragma once
#include "FeatureManipulator.hpp"

// Interface that defines a common handle() method for all altars.
class AltarManipulator : public FeatureManipulator
{
  public:
    AltarManipulator(FeaturePtr feature);

    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool desecrate(CreaturePtr creature, MapPtr current_map) override;

    virtual std::string get_creature_action_key() const = 0;
};

