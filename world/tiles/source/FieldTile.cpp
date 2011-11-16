#include "FieldTile.hpp"

TileType FieldTile::get_tile_type() const
{
  return TILE_TYPE_FIELD;
}

#ifdef UNIT_TESTS
#include "unit_tests/FieldTile_test.cpp"
#endif
