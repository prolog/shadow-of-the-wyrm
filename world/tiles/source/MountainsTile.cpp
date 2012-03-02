#include "MountainsTile.hpp"

TileType MountainsTile::get_tile_type() const
{
  return TILE_TYPE_MOUNTAINS;
}

std::string MountainsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_MOUNTAINS;
}

#ifdef UNIT_TESTS
#include "unit_tests/MountainsTile_test.cpp"
#endif
