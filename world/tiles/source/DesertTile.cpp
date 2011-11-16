#include "DesertTile.hpp"

TileType DesertTile::get_tile_type() const
{
  return TILE_TYPE_DESERT;
}

#ifdef UNIT_TESTS
#include "unit_tests/DesertTile_test.cpp"
#endif
