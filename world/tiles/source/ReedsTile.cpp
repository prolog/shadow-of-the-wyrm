#include "ReedsTile.hpp"

TileType ReedsTile::get_tile_type() const
{
  return TILE_TYPE_REEDS;
}

std::string ReedsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_REEDS;
}

Tile* ReedsTile::clone()
{
  return new ReedsTile(*this);
}

ClassIdentifier ReedsTile::internal_class_identifier() const
{
  return CLASS_ID_REEDS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ReedsTile_test.cpp"
#endif
