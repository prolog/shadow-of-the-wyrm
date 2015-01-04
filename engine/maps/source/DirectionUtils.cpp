#include "DirectionUtils.hpp"

DirectionUtils::DirectionUtils()
{
}

bool DirectionUtils::is_cardinal(const Direction d)
{
  switch(d)
  {
    case Direction::DIRECTION_NORTH:
    case Direction::DIRECTION_SOUTH:
    case Direction::DIRECTION_EAST:
    case Direction::DIRECTION_WEST:
      return true;
    default:
      return false;
  }
}

bool DirectionUtils::is_ordinal(const Direction d)
{
  switch(d)
  {
    case Direction::DIRECTION_NORTH_WEST:
    case Direction::DIRECTION_NORTH_EAST:
    case Direction::DIRECTION_SOUTH_WEST:
    case Direction::DIRECTION_SOUTH_EAST:
      return true;
    default:
      return false;
  }
}

Direction DirectionUtils::get_opposite_direction(const Direction d)
{
  Direction o = d;

  switch (d)
  {
    case Direction::DIRECTION_UP:
      o = Direction::DIRECTION_DOWN;
      break;
    case Direction::DIRECTION_DOWN:
      o = Direction::DIRECTION_UP;
      break;
    case Direction::DIRECTION_NORTH_WEST:
      o = Direction::DIRECTION_SOUTH_EAST;
      break;
    case Direction::DIRECTION_NORTH:
      o = Direction::DIRECTION_SOUTH;
      break;
    case Direction::DIRECTION_NORTH_EAST:
      o = Direction::DIRECTION_SOUTH_WEST;
      break;
    case Direction::DIRECTION_WEST:
      o = Direction::DIRECTION_EAST;
      break;
    case Direction::DIRECTION_EAST:
      o = Direction::DIRECTION_WEST;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      o = Direction::DIRECTION_NORTH_EAST;
      break;
    case Direction::DIRECTION_SOUTH:
      o = Direction::DIRECTION_NORTH;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      o = Direction::DIRECTION_NORTH_WEST;
      break;
    case Direction::DIRECTION_NULL:
    default:
      break;
  }

  return o;
}

#ifdef UNIT_TESTS
#include "unit_tests/DirectionUtils_test.cpp"
#endif
