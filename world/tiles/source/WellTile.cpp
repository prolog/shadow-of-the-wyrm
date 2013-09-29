#include "WellTile.hpp"

TileType WellTile::get_tile_type() const
{
  return TILE_TYPE_WELL;
}

std::string WellTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WELL;
}

Tile* WellTile::clone()
{
  return new WellTile(*this);
}

ClassIdentifier WellTile::internal_class_identifier() const
{
  return CLASS_ID_WELL_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/WellTile_test.cpp"
#endif
