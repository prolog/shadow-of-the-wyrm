#include "CairnTile.hpp"

TileType CairnTile::get_tile_type() const
{
  return TILE_TYPE_CAIRN;
}

#ifdef UNIT_TESTS
#include "unit_tests/CairnTile_test.cpp"
#endif
