#include "MountainsTile.hpp"

TileType MountainsTile::get_tile_type() const
{
  return TILE_TYPE_MOUNTAINS;
}

#ifdef UNIT_TESTS
#include "unit_tests/MountainsTile_test.cpp"
#endif
