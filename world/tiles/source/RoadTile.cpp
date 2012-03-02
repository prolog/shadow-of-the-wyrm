#include "RoadTile.hpp"

TileType RoadTile::get_tile_type() const
{
  return TILE_TYPE_ROAD;
}

std::string RoadTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ROAD;
}

#ifdef UNIT_TESTS
#include "unit_tests/RoadTile_test.cpp"
#endif
