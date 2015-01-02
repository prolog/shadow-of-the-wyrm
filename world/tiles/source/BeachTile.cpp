#include "BeachTile.hpp"

TileType BeachTile::get_tile_type() const
{
  return TILE_TYPE_BEACH;
}

std::string BeachTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BEACH;
}

Tile* BeachTile::clone()
{
  return new BeachTile(*this);
}

ClassIdentifier BeachTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BEACH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/BeachTile_test.cpp"
#endif
