#include "CavernTile.hpp"

TileType CavernTile::get_tile_type() const
{
  return TILE_TYPE_CAVERN;
}

#ifdef UNIT_TESTS
#include "unit_tests/CavernTile_test.cpp"
#endif
