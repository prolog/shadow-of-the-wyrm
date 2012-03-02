#include "GraveTile.hpp"

TileType GraveTile::get_tile_type() const
{
  return TILE_TYPE_GRAVE;
}

std::string GraveTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_GRAVE;
}

#ifdef UNIT_TESTS
#include "unit_tests/GraveTile_test.cpp"
#endif
