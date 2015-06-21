#include "MovementAccumulator.hpp"
#include "MovementAccumulation.hpp"

void MovementAccumulator::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();

    movement_accumulation.set_minutes_on_super_type_given_movement(movement_accumulation.get_minutes_on_super_type_given_movement() + minutes_this_tick);
    movement_accumulation.set_minutes_on_tile_type_given_movement(movement_accumulation.get_minutes_on_tile_type_given_movement() + minutes_this_tick);
  }
}
