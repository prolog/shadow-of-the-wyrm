#include "DownStaircaseTile.hpp"

TileType DownStaircaseTile::get_tile_type() const
{
  return TILE_TYPE_DOWN_STAIRCASE;
}

StaircaseType DownStaircaseTile::get_staircase_type() const
{
  return STAIRCASE_DOWN;
}

#ifdef UNIT_TESTS
#include "unit_tests/DownStaircaseTile_test.cpp"
#endif
