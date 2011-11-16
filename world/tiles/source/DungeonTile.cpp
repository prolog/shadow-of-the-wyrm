#include "DungeonTile.hpp"

TileType DungeonTile::get_tile_type() const
{
  return TILE_TYPE_DUNGEON;
}

#ifdef UNIT_TESTS
#include "unit_tests/DungeonTile_test.cpp"
#endif
