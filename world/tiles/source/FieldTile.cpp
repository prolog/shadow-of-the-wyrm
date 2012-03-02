#include "FieldTile.hpp"

TileType FieldTile::get_tile_type() const
{
  return TILE_TYPE_FIELD;
}

std::string FieldTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_FIELD;
}

#ifdef UNIT_TESTS
#include "unit_tests/FieldTile_test.cpp"
#endif
