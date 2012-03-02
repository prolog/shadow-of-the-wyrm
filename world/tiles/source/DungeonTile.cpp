#include "DungeonTile.hpp"

TileType DungeonTile::get_tile_type() const
{
  return TILE_TYPE_DUNGEON;
}

std::string DungeonTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DUNGEON;
}

#ifdef UNIT_TESTS
#include "unit_tests/DungeonTile_test.cpp"
#endif
