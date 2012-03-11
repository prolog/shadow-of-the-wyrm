#include "DungeonTile.hpp"

// Individual floor tiles
TileType DungeonTile::get_tile_type() const
{
  return TILE_TYPE_DUNGEON;
}

std::string DungeonTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DUNGEON;
}

// Dungeon complexes on the world map
TileType DungeonComplexTile::get_tile_type() const
{
  return TILE_TYPE_DUNGEON_COMPLEX;
}

std::string DungeonComplexTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DUNGEON_COMPLEX;
}
#ifdef UNIT_TESTS
#include "unit_tests/DungeonTile_test.cpp"
#endif
