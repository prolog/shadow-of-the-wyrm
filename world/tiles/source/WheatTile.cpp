#include "WheatTile.hpp"

TileType WheatTile::get_tile_type() const
{
  return TILE_TYPE_WHEAT;
}

#ifdef UNIT_TESTS
#include "unit_tests/WheatTile_test.cpp"
#endif
