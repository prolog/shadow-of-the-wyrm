#include "RockTile.hpp"

TileType RockTile::get_tile_type() const
{
  return TILE_TYPE_ROCK;
}

#ifdef UNIT_TESTS
#include "unit_tests/RockTile_test.cpp"
#endif
