#include "SeaTile.hpp"

TileType SeaTile::get_tile_type() const
{
  return TILE_TYPE_SEA;
}

std::string SeaTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SEA;
}

#ifdef UNIT_TESTS
#include "unit_tests/SeaTile_test.cpp"
#endif
