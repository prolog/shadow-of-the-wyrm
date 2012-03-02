#include "DownStaircaseTile.hpp"

TileType DownStaircaseTile::get_tile_type() const
{
  return TILE_TYPE_DOWN_STAIRCASE;
}

StaircaseType DownStaircaseTile::get_staircase_type() const
{
  return STAIRCASE_DOWN;
}

std::string DownStaircaseTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DOWN_STAIRCASE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DownStaircaseTile_test.cpp"
#endif
