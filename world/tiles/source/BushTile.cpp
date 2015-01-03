#include "BushTile.hpp"

TileType BushTile::get_tile_type() const
{
  return TileType::TILE_TYPE_BUSH;
}

std::string BushTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BUSH;
}

Tile* BushTile::clone()
{
  return new BushTile(*this);
}

ClassIdentifier BushTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BUSH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/BushTile_test.cpp"
#endif
