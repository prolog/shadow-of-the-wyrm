#include "RoadTile.hpp"

TileType RoadTile::get_tile_type() const
{
  return TILE_TYPE_ROAD;
}

#ifdef UNIT_TESTS
#include "unit_tests/RoadTile_test.cpp"
#endif
