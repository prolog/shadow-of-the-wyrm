#include "MovementAccumulation.hpp"
#include "Serialize.hpp"

using namespace std;

MovementAccumulation::MovementAccumulation()
{
  reset();
}

bool MovementAccumulation::operator==(const MovementAccumulation& movement) const
{
  bool result = true;

  result = result && (minutes_on_super_type_given_movement == movement.minutes_on_super_type_given_movement);
  result = result && (tile_super_type == movement.tile_super_type);
  result = result && (minutes_on_tile_type_given_movement == movement.minutes_on_tile_type_given_movement);
  result = result && (tile_type == movement.tile_type);
  result = result && (movement_type == movement.movement_type);

  return result;
}

// Reset all the values back to the default
void MovementAccumulation::reset()
{
  minutes_on_super_type_given_movement = 0;
  minutes_on_tile_type_given_movement = 0;
  tile_type = TileType::TILE_TYPE_UNDEFINED;
  tile_super_type = TileSuperType::TILE_SUPER_TYPE_UNDEFINED;
  frozen = false;
  movement_type = MovementType::MOVEMENT_TYPE_WALKING;
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

void MovementAccumulation::set_tile_frozen(const bool new_frozen)
{
  frozen = new_frozen;
}

bool MovementAccumulation::get_tile_frozen() const
{
  return frozen;
}

void MovementAccumulation::set_movement_type(const MovementType new_type)
{
  movement_type = new_type;
}

MovementType MovementAccumulation::get_movement_type() const
{
  return movement_type;
}

bool MovementAccumulation::serialize(ostream& stream) const
{
  Serialize::write_ulonglong(stream, minutes_on_super_type_given_movement);
  Serialize::write_enum(stream, tile_super_type);
  Serialize::write_ulonglong(stream, minutes_on_tile_type_given_movement);
  Serialize::write_enum(stream, tile_type);
  Serialize::write_bool(stream, frozen);
  Serialize::write_enum(stream, movement_type);

  return true;
}

bool MovementAccumulation::deserialize(istream& stream)
{
  Serialize::read_ulonglong(stream, minutes_on_super_type_given_movement);
  Serialize::read_enum(stream, tile_super_type);
  Serialize::read_ulonglong(stream, minutes_on_tile_type_given_movement);
  Serialize::read_enum(stream, tile_type);
  Serialize::read_bool(stream, frozen);
  Serialize::read_enum(stream, movement_type);

  return true;
}

ClassIdentifier MovementAccumulation::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MOVEMENT_ACCUMULATION;
}

#ifdef UNIT_TESTS
#include "unit_tests/MovementAccumulation_test.cpp"
#endif

