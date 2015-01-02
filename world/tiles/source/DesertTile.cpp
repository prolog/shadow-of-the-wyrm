#include "DesertTile.hpp"

TileType DesertTile::get_tile_type() const
{
  return TILE_TYPE_DESERT;
}

std::string DesertTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DESERT;
}

Tile* DesertTile::clone()
{
  return new DesertTile(*this);
}

ClassIdentifier DesertTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DESERT_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DesertTile_test.cpp"
#endif
