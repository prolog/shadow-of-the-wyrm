#include "BushTile.hpp"

TileType BushTile::get_tile_type() const
{
  return TILE_TYPE_BUSH;
}

#ifdef UNIT_TESTS
#include "unit_tests/BushTile_test.cpp"
#endif
