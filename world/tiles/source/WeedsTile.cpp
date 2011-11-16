#include "WeedsTile.hpp"

TileType WeedsTile::get_tile_type() const
{
  return TILE_TYPE_WEEDS;
}

#ifdef UNIT_TESTS
#include "unit_tests/WeedsTile_test.cpp"
#endif
