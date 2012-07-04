#include "MovementAccumulationUpdater.hpp"

void MovementAccumulationUpdater::update(CreaturePtr creature, TilePtr new_tile)
{
  if (creature && new_tile)
  {
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();

    TileSuperType old_super_type = movement_accumulation.get_tile_super_type();
    TileSuperType new_super_type = new_tile->get_tile_super_type();

    TileType old_tile_type = movement_accumulation.get_tile_type();
    TileType new_tile_type = new_tile->get_tile_type();
    
    MovementType old_movement_type = movement_accumulation.get_movement_type();
    MovementType new_movement_type = get_movement_type(creature, new_tile);
    
    if (old_movement_type != new_movement_type)
    {
      movement_accumulation.reset();
      movement_accumulation.set_movement_type(new_movement_type);
    }
    
    if (old_super_type != new_super_type)
    {
      movement_accumulation.set_tile_super_type(new_super_type);
      movement_accumulation.set_minutes_on_super_type_given_movement(0);
    }
        
    if (old_tile_type != new_tile_type)
    {
      movement_accumulation.set_tile_type(new_tile_type);
      movement_accumulation.set_minutes_on_tile_type_given_movement(0);
    }
  }
}

// If the super type is ground, return either MOVEMENT_TYPE_WALKING
// or MOVEMENT_TYPE_FLYING.  If the super type is water, return any of
// MovementType's values. (one can carry a boat on load, but can't use it
// as a method of transportation.)
MovementType MovementAccumulationUpdater::get_movement_type(CreaturePtr creature, TilePtr tile)
{
  MovementType movement = MOVEMENT_TYPE_WALKING;

  if (creature && tile)
  {
    TileSuperType tst = tile->get_tile_super_type();
    
    switch (tst)
    {
      case TILE_SUPER_TYPE_UNDEFINED:
      case TILE_SUPER_TYPE_GROUND:
        break;
      case TILE_SUPER_TYPE_WATER:
      default:
        if (creature->get_inventory().has_item_type(ITEM_TYPE_BOAT))
        {
          movement = MOVEMENT_TYPE_BOAT;
        }
        break;
    }
  }

  return movement;
}
