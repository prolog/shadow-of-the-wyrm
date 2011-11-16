#include "RiverTile.hpp"

TileType RiverTile::get_tile_type() const
{
  return TILE_TYPE_RIVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/RiverTile_test.cpp"
#endif
