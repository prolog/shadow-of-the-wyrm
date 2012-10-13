#include "ShoalsTile.hpp"

TileType ShoalsTile::get_tile_type() const
{
  return TILE_TYPE_SHOALS;
}

TileSuperType ShoalsTile::get_tile_super_type() const
{
  return TILE_SUPER_TYPE_WATER;
}

std::string ShoalsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SHOALS;
}

Tile* ShoalsTile::clone()
{
  return new ShoalsTile(*this);
}

ClassIdentifier ShoalsTile::internal_class_identifier() const
{
  return CLASS_ID_SHOALS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShoalsTile_test.cpp"
#endif
