#include "GraveTile.hpp"

TileType GraveTile::get_tile_type() const
{
  return TILE_TYPE_GRAVE;
}

#ifdef UNIT_TESTS
#include "unit_tests/GraveTile_test.cpp"
#endif
