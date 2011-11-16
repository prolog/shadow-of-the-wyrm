#include "SpringsTile.hpp"

TileType SpringsTile::get_tile_type() const
{
  return TILE_TYPE_SPRINGS;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpringsTile_test.cpp"
#endif
