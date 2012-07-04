#include "MovementAccumulation.hpp"

MovementAccumulation::MovementAccumulation()
{
  reset();
}

// Reset all the values back to the default
void MovementAccumulation::reset()
{
  minutes_on_super_type_given_movement = 0;
  minutes_on_tile_type_given_movement = 0;
  tile_type = TILE_TYPE_UNDEFINED;
  tile_super_type = TILE_SUPER_TYPE_UNDEFINED;
  movement_type = MOVEMENT_TYPE_WALKING;
}

void MovementAccumulation::set_minutes_on_super_type_given_movement(const ulonglong new_minutes)
{
  minutes_on_super_type_given_movement = new_minutes;
}

ulonglong MovementAccumulation::get_minutes_on_super_type_given_movement() const
{
  return minutes_on_super_type_given_movement;
}

void MovementAccumulation::set_tile_super_type(const TileSuperType new_super_type)
{
  tile_super_type = new_super_type;
}

TileSuperType MovementAccumulation::get_tile_super_type() const
{
  return tile_super_type;
}

void MovementAccumulation::set_minutes_on_tile_type_given_movement(const ulonglong new_minutes)
{
  minutes_on_tile_type_given_movement = new_minutes;
}

ulonglong MovementAccumulation::get_minutes_on_tile_type_given_movement() const
{
  return minutes_on_tile_type_given_movement;
}

void MovementAccumulation::set_tile_type(const TileType new_type)
{
  tile_type = new_type;
}

TileType MovementAccumulation::get_tile_type() const
{
  return tile_type;
}

void MovementAccumulation::set_movement_type(const MovementType new_type)
{
  movement_type = new_type;
}

MovementType MovementAccumulation::get_movement_type() const
{
  return movement_type;
}
