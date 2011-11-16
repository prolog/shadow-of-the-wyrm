#include "ScrubTile.hpp"

TileType ScrubTile::get_tile_type() const
{
  return TILE_TYPE_SCRUB;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScrubTile_test.cpp"
#endif
