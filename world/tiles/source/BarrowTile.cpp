#include "BarrowTile.hpp"

TileType BarrowTile::get_tile_type() const
{
  return TileType::TILE_TYPE_BARROW;
}

std::string BarrowTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BARROW;
}

Tile* BarrowTile::clone()
{
  return new BarrowTile(*this);
}

ClassIdentifier BarrowTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BARROW_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/BarrowTile_test.cpp"
#endif
