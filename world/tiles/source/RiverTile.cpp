#include "RiverTile.hpp"

TileType RiverTile::get_tile_type() const
{
  return TILE_TYPE_RIVER;
}

std::string RiverTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_RIVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/RiverTile_test.cpp"
#endif
