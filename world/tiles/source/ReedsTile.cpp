#include "ReedsTile.hpp"

TileType ReedsTile::get_tile_type() const
{
  return TILE_TYPE_REEDS;
}

#ifdef UNIT_TESTS
#include "unit_tests/ReedsTile_test.cpp"
#endif
