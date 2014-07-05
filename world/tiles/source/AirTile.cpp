#include "AirTile.hpp"

TileType AirTile::get_tile_type() const
{
  return TILE_TYPE_AIR;
}

TileSuperType AirTile::get_tile_super_type() const
{
  return TILE_SUPER_TYPE_AIR;
}

std::string AirTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_AIR;
}

Tile* AirTile::clone()
{
  return new AirTile(*this);
}

ClassIdentifier AirTile::internal_class_identifier() const
{
  return CLASS_ID_AIR_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/AirTile_test.cpp"
#endif

