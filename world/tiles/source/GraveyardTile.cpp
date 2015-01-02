#include "GraveyardTile.hpp"

TileType GraveyardTile::get_tile_type() const
{
  return TILE_TYPE_GRAVEYARD;
}

std::string GraveyardTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_GRAVEYARD;
}

Tile* GraveyardTile::clone()
{
  return new GraveyardTile(*this);
}

ClassIdentifier GraveyardTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GRAVEYARD_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/GraveyardTile_test.cpp"
#endif
