#include "WheatTile.hpp"

TileType WheatTile::get_tile_type() const
{
  return TILE_TYPE_WHEAT;
}

std::string WheatTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WHEAT;
}

#ifdef UNIT_TESTS
#include "unit_tests/WheatTile_test.cpp"
#endif
