#include "SewerTile.hpp"

// Individual floor tiles
TileType SewerTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SEWER;
}

std::string SewerTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SEWER;
}

Tile* SewerTile::clone()
{
  return new SewerTile(*this);
}

ClassIdentifier SewerTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SEWER_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SewerTile_test.cpp"
#endif
