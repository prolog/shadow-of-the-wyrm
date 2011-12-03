#include "UpStaircaseTile.hpp"

TileType UpStaircaseTile::get_tile_type() const
{
  return TILE_TYPE_UP_STAIRCASE;
}

StaircaseType UpStaircaseTile::get_staircase_type() const
{
  return STAIRCASE_UP;
}

#ifdef UNIT_TESTS
#include "unit_tests/UpStaircaseTile_test.cpp"
#endif
