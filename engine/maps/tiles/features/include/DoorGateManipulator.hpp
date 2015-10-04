#pragma once
#include "IFeatureManipulator.hpp"

class DoorGateManipulator : public IFeatureManipulator
{
  public:
    DoorGateManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    void break_down_door(CreaturePtr creature, TilePtr feature_tile);
    void handle_sprain_if_necessary(CreaturePtr creature, const int pct_chance);

    static const int PCT_CHANCE_SPRAIN_LEG_BUCKLE;
    static const int PCT_CHANCE_SPRAIN_LEG_UNMOVED;
    static const int SPRAIN_DAMAGE_MIN;
    static const int SPRAIN_DAMAGE_MAX;
};

