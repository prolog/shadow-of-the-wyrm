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
