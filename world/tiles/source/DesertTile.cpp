#include "DesertTile.hpp"

TileType DesertTile::get_tile_type() const
{
  return TILE_TYPE_DESERT;
}

std::string DesertTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DESERT;
}

#ifdef UNIT_TESTS
#include "unit_tests/DesertTile_test.cpp"
#endif
