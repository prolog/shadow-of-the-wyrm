#include "ForestTile.hpp"

TileType ForestTile::get_tile_type() const
{
  return TILE_TYPE_FOREST;
}

#ifdef UNIT_TESTS
#include "unit_tests/ForestTile_test.cpp"
#endif
