#include "DungeonTile.hpp"

// Individual floor tiles
TileType DungeonTile::get_tile_type() const
{
  return TileType::TILE_TYPE_DUNGEON;
}

std::string DungeonTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DUNGEON;
}

bool DungeonTile::is_interior() const
{
  return true;
}

Tile* DungeonTile::clone()
{
  return new DungeonTile(*this);
}

ClassIdentifier DungeonTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DUNGEON_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DungeonTile_test.cpp"
#endif
