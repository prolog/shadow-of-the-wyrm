#include "SeaTile.hpp"

TileType SeaTile::get_tile_type() const
{
  return TILE_TYPE_SEA;
}

#ifdef UNIT_TESTS
#include "unit_tests/SeaTile_test.cpp"
#endif
