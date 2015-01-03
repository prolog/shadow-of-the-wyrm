#include "CavernTile.hpp"

TileType CavernTile::get_tile_type() const
{
  return TileType::TILE_TYPE_CAVERN;
}

std::string CavernTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CAVERN;
}

Tile* CavernTile::clone()
{
  return new CavernTile(*this);
}

ClassIdentifier CavernTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CAVERN_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/CavernTile_test.cpp"
#endif
