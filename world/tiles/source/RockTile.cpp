#include "RockTile.hpp"

TileType RockTile::get_tile_type() const
{
  return TILE_TYPE_ROCK;
}

std::string RockTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_ROCK;
}

bool RockTile::get_is_blocking() const
{
  return true;
}

int RockTile::get_movement_multiplier() const
{
  return 0;
}

#ifdef UNIT_TESTS
#include "unit_tests/RockTile_test.cpp"
#endif
