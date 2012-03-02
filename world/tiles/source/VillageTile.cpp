#include "VillageTile.hpp"

TileType VillageTile::get_tile_type() const
{
  return TILE_TYPE_VILLAGE;
}

std::string VillageTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_VILLAGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/VillageTile_test.cpp"
#endif
