#include "DirectionUtils.hpp"

DirectionUtils::DirectionUtils()
{
}

bool DirectionUtils::is_cardinal(const Direction d)
{
  switch(d)
  {
    case DIRECTION_NORTH:
    case DIRECTION_SOUTH:
    case DIRECTION_EAST:
    case DIRECTION_WEST:
      return true;
    default:
      return false;
  }
}

bool DirectionUtils::is_ordinal(const Direction d)
{
  switch(d)
  {
    case DIRECTION_NORTH_WEST:
    case DIRECTION_NORTH_EAST:
    case DIRECTION_SOUTH_WEST:
    case DIRECTION_SOUTH_EAST:
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
    case DIRECTION_UP:
      o = DIRECTION_DOWN;
      break;
    case DIRECTION_DOWN:
      o = DIRECTION_UP;
      break;
    case DIRECTION_NORTH_WEST:
      o = DIRECTION_SOUTH_EAST;
      break;
    case DIRECTION_NORTH:
      o = DIRECTION_SOUTH;
      break;
    case DIRECTION_NORTH_EAST:
      o = DIRECTION_SOUTH_WEST;
      break;
    case DIRECTION_WEST:
      o = DIRECTION_EAST;
      break;
    case DIRECTION_EAST:
      o = DIRECTION_WEST;
      break;
    case DIRECTION_SOUTH_WEST:
      o = DIRECTION_NORTH_EAST;
      break;
    case DIRECTION_SOUTH:
      o = DIRECTION_NORTH;
      break;
    case DIRECTION_SOUTH_EAST:
      o = DIRECTION_NORTH_WEST;
      break;
    case DIRECTION_NULL:
    default:
      break;
  }

  return o;
}

#ifdef UNIT_TESTS
#include "unit_tests/DirectionUtils_test.cpp"
#endif
