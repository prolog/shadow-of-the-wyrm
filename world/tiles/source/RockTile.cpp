#include "RockTile.hpp"

TileType RockTile::get_tile_type() const
{
  return TILE_TYPE_ROCK;
}

std::string RockTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ROCK;
}

#ifdef UNIT_TESTS
#include "unit_tests/RockTile_test.cpp"
#endif
