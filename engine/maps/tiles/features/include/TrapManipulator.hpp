#pragma once
#include "IFeatureManipulator.hpp"
#include "Trap.hpp"

class TrapManipulator : public IFeatureManipulator
{
  public:
    TrapManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    void trigger_trap(TrapPtr trap, CreaturePtr creature);
    void apply_effects_to_creature(TrapPtr trap, CreaturePtr creature);
    void create_item_if_necessary(TilePtr tile, TrapPtr trap);
    void create_and_draw_animation(TrapPtr trap, CreaturePtr creature, const Coordinate& creature_coord);
};

