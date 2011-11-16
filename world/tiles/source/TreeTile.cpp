#include "TreeTile.hpp"

TileType TreeTile::get_tile_type() const
{
  return TILE_TYPE_TREE;
}

#ifdef UNIT_TESTS
#include "unit_tests/TreeTile_test.cpp"
#endif
