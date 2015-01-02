#include "PierTile.hpp"

TileType PierTile::get_tile_type() const
{
  return TILE_TYPE_PIER;
}

std::string PierTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_PIER;
}

Tile* PierTile::clone()
{
  return new PierTile(*this);
}

ClassIdentifier PierTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PIER_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/PierTile_test.cpp"
#endif
