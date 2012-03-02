#include "ScrubTile.hpp"

TileType ScrubTile::get_tile_type() const
{
  return TILE_TYPE_SCRUB;
}

std::string ScrubTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SCRUB;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScrubTile_test.cpp"
#endif
