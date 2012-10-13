#include "FieldTile.hpp"

TileType FieldTile::get_tile_type() const
{
  return TILE_TYPE_FIELD;
}

std::string FieldTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_FIELD;
}

Tile* FieldTile::clone()
{
  return new FieldTile(*this);
}

ClassIdentifier FieldTile::internal_class_identifier() const
{
  return CLASS_ID_FIELD_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/FieldTile_test.cpp"
#endif
