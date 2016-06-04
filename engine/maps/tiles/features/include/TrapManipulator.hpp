#pragma once
#include "IFeatureManipulator.hpp"
#include "Trap.hpp"

class TrapManipulator : public IFeatureManipulator
{
  public:
    TrapManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    void trigger_trap(TrapPtr trap, CreaturePtr creature);
    void apply_effects_to_creature(TrapPtr trap, CreaturePtr creature);
    void create_item_if_necessary(TilePtr tile, TrapPtr trap);
    void create_and_draw_animation(TrapPtr trap, CreaturePtr creature, const Coordinate& creature_coord);
};

