#include "HillsTile.hpp"

TileType HillsTile::get_tile_type() const
{
  return TILE_TYPE_HILLS;
}

std::string HillsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_HILLS;
}

#ifdef UNIT_TESTS
#include "unit_tests/HillsTile_test.cpp"
#endif
