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
      movement_accumulation.set_tile_super_type(new_super_type);
      movement_accumulation.set_tile_type(new_tile_type);
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
  // Can always walk or fly.
  //
  // Boating is only allowed on water.
  MovementType movement = MovementType::MOVEMENT_TYPE_WALKING;

  if (creature && creature->has_status(StatusIdentifiers::STATUS_ID_FLYING) || creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
  {
    movement = MovementType::MOVEMENT_TYPE_FLYING;
  }

  if (creature && tile)
  {
    TileSuperType tst = tile->get_tile_super_type();
    
    switch (tst)
    {
      case TileSuperType::TILE_SUPER_TYPE_UNDEFINED:
      case TileSuperType::TILE_SUPER_TYPE_GROUND:
      case TileSuperType::TILE_SUPER_TYPE_AIR:
        break;
      case TileSuperType::TILE_SUPER_TYPE_WATER:
      default:
        if (creature->get_inventory()->has_item_type(ItemType::ITEM_TYPE_BOAT))
        {
          movement = MovementType::MOVEMENT_TYPE_BOAT;
        }
        break;
    }
  }

  return movement;
}
