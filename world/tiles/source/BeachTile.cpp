#include "BeachTile.hpp"

TileType BeachTile::get_tile_type() const
{
  return TILE_TYPE_BEACH;
}

#ifdef UNIT_TESTS
#include "unit_tests/BeachTile_test.cpp"
#endif
