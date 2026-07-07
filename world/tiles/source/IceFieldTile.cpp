#include "IceFieldTile.hpp"

TileType IceFieldTile::get_tile_type() const
{
  return TileType::TILE_TYPE_ICE_FIELD;
}

std::string IceFieldTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ICE_FIELD;
}

Tile* IceFieldTile::clone()
{
  return new IceFieldTile(*this);
}

ClassIdentifier IceFieldTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ICE_FIELD_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/IceFieldTile_test.cpp"
#endif
