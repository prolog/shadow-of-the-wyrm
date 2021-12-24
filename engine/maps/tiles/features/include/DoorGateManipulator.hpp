#pragma once
#include "Features.hpp"
#include "FeatureManipulator.hpp"
#include "MessageManagerFactory.hpp"

class DoorGateManipulator : public FeatureManipulator
{
  public:
    DoorGateManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    void kick_closed_door(IMessageManager& manager, EntrancePtr entr, CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature);
    void kick_open_door(IMessageManager& manager, EntrancePtr entr);
    void break_down_door(CreaturePtr creature, TilePtr feature_tile);
    void handle_sprain_if_necessary(CreaturePtr creature, const int pct_chance);

    static const int PCT_CHANCE_SPRAIN_LEG_BUCKLE;
    static const int PCT_CHANCE_SPRAIN_LEG_UNMOVED;
    static const int SPRAIN_DAMAGE_MIN;
    static const int SPRAIN_DAMAGE_MAX;
};

