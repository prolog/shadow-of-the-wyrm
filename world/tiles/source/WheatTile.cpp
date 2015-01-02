#include "WheatTile.hpp"

TileType WheatTile::get_tile_type() const
{
  return TILE_TYPE_WHEAT;
}

std::string WheatTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WHEAT;
}

Tile* WheatTile::clone()
{
  return new WheatTile(*this);
}

ClassIdentifier WheatTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WHEAT_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/WheatTile_test.cpp"
#endif
