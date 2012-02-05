#include "VillageTile.hpp"

TileType VillageTile::get_tile_type() const
{
  return TILE_TYPE_VILLAGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/VillageTile_test.cpp"
#endif
