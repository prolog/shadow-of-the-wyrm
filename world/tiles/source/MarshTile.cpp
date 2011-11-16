#include "MarshTile.hpp"

TileType MarshTile::get_tile_type() const
{
  return TILE_TYPE_MARSH;
}

#ifdef UNIT_TESTS
#include "unit_tests/MarshTile_test.cpp"
#endif
