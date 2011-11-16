#include "ShoalsTile.hpp"

TileType ShoalsTile::get_tile_type() const
{
  return TILE_TYPE_SHOALS;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShoalsTile_test.cpp"
#endif
