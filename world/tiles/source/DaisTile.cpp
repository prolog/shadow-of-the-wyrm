#include "DaisTile.hpp"

// Individual raised floor tiles
TileType DaisTile::get_tile_type() const
{
  return TILE_TYPE_DAIS;
}

std::string DaisTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DAIS;
}

#ifdef UNIT_TESTS
#include "unit_tests/DaisTile_test.cpp"
#endif
