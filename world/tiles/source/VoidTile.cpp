#include "VoidTile.hpp"

TileType VoidTile::get_tile_type() const
{
  return TileType::TILE_TYPE_VOID;
}

std::string VoidTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_VOID;
}

Tile* VoidTile::clone()
{
  return new VoidTile(*this);
}

ClassIdentifier VoidTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_VOID_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/VoidTile_test.cpp"
#endif
