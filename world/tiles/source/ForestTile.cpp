#include "ForestTile.hpp"

TileType ForestTile::get_tile_type() const
{
  return TILE_TYPE_FOREST;
}

std::string ForestTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_FOREST;
}

Tile* ForestTile::clone()
{
  return new ForestTile(*this);
}

ClassIdentifier ForestTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FOREST_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ForestTile_test.cpp"
#endif
