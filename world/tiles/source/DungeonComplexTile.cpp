#include "DungeonComplexTile.hpp"

// Dungeon complexes on the world map
TileType DungeonComplexTile::get_tile_type() const
{
  return TILE_TYPE_DUNGEON_COMPLEX;
}

std::string DungeonComplexTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DUNGEON_COMPLEX;
}
