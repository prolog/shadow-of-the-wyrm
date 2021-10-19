#include "DirectionUtils.hpp"
#include "RNG.hpp"

using namespace std;

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

vector<CardinalDirection> DirectionUtils::get_perpendicular_directions(const CardinalDirection cd)
{
  vector<CardinalDirection> dirs;

  switch (cd)
  {
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
      dirs = {CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST};
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
      dirs = {CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH};
      break;
    case CardinalDirection::CARDINAL_DIRECTION_NULL:
    default:
      break;
  }

  return dirs;
}

Direction DirectionUtils::to_direction(const CardinalDirection cd)
{
  Direction d = Direction::DIRECTION_NULL;

  switch (cd)
  {
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
      d = Direction::DIRECTION_NORTH;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
      d = Direction::DIRECTION_SOUTH;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
      d = Direction::DIRECTION_EAST;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
      d = Direction::DIRECTION_WEST;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_NULL:
    default:
      d = Direction::DIRECTION_NULL;
      break;
  }

  return d;
}

CardinalDirection DirectionUtils::to_cardinal_direction(const Direction d)
{
  CardinalDirection cd = CardinalDirection::CARDINAL_DIRECTION_NULL;

  switch (d)
  {
    case Direction::DIRECTION_NORTH_EAST:
    case Direction::DIRECTION_NORTH_WEST:
    case Direction::DIRECTION_NORTH:
      cd = CardinalDirection::CARDINAL_DIRECTION_NORTH;
      break;
    case Direction::DIRECTION_WEST:
      cd = CardinalDirection::CARDINAL_DIRECTION_WEST;
      break;
    case Direction::DIRECTION_EAST:
      cd = CardinalDirection::CARDINAL_DIRECTION_EAST;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
    case Direction::DIRECTION_SOUTH_WEST:
    case Direction::DIRECTION_SOUTH:
      cd = CardinalDirection::CARDINAL_DIRECTION_SOUTH;
      break;
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    default:
      break;
  }

  return cd;
}

CardinalDirection DirectionUtils::get_opposite_direction(const CardinalDirection d)
{
  CardinalDirection o = d;

  switch (d)
  {
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
      o = CardinalDirection::CARDINAL_DIRECTION_SOUTH;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
      o = CardinalDirection::CARDINAL_DIRECTION_NORTH;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
      o = CardinalDirection::CARDINAL_DIRECTION_WEST;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
      o = CardinalDirection::CARDINAL_DIRECTION_EAST;
    default:
      break;
  }

  return o;
}

CardinalDirection DirectionUtils::get_random_cardinal_direction(const vector<CardinalDirection>& dirs)
{
  if (dirs.empty())
  {
    return get_random_cardinal_direction();
  }
  else
  {
    CardinalDirection cd = CardinalDirection::CARDINAL_DIRECTION_NULL;

    if (!dirs.empty())
    {
      cd = dirs[RNG::range(0, dirs.size() - 1)];
    }

    return cd;
  }
}
CardinalDirection DirectionUtils::get_random_cardinal_direction()
{
  vector<CardinalDirection> gate_dirs = { CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH, CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST };
  return gate_dirs[RNG::range(0, gate_dirs.size() - 1)];
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

bool DirectionUtils::direction_matches_category(const Direction d, const DirectionCategory dc)
{
  bool matches = false;

  switch (dc)
  {
    case DirectionCategory::DIRECTION_CATEGORY_CARDINAL:
      matches = DirectionUtils::is_cardinal(d) || d == Direction::DIRECTION_NULL;
      break;
    case DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL:
      matches = (DirectionUtils::is_ordinal(d) || DirectionUtils::is_cardinal(d)) || d == Direction::DIRECTION_NULL;
      break;
    case DirectionCategory::DIRECTION_CATEGORY_NONE:
      break;
  }

  return matches;
}

set<Direction> DirectionUtils::get_all_directions_for_category(DirectionCategory dc)
{
  set<Direction> directions;

  switch (dc)
  {
    case DirectionCategory::DIRECTION_CATEGORY_CARDINAL:
      directions = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST};
      break;
    case DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL:
      directions = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST, Direction::DIRECTION_NORTH_EAST, Direction::DIRECTION_NORTH_WEST, Direction::DIRECTION_SOUTH_EAST, Direction::DIRECTION_SOUTH_WEST};
      break;
    case DirectionCategory::DIRECTION_CATEGORY_NONE:
      directions.insert(Direction::DIRECTION_NULL);
      break;
  }

  return directions;
}

#ifdef UNIT_TESTS
#include "unit_tests/DirectionUtils_test.cpp"
#endif
