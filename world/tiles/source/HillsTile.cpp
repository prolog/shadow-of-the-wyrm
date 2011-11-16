#include "HillsTile.hpp"

TileType HillsTile::get_tile_type() const
{
  return TILE_TYPE_HILLS;
}

#ifdef UNIT_TESTS
#include "unit_tests/HillsTile_test.cpp"
#endif
