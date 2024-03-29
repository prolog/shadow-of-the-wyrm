#include "DungeonComplexTile.hpp"

// Dungeon complexes on the world map
TileType DungeonComplexTile::get_tile_type() const
{
  return TileType::TILE_TYPE_DUNGEON_COMPLEX;
}

std::string DungeonComplexTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DUNGEON_COMPLEX;
}

bool DungeonComplexTile::is_interior() const
{
  return true;
}

Tile* DungeonComplexTile::clone()
{
  return new DungeonComplexTile(*this);
}

ClassIdentifier DungeonComplexTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DUNGEON_COMPLEX_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DungeonComplexTile_test.cpp"
#endif
