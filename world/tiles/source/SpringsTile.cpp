#include "SpringsTile.hpp"

TileType SpringsTile::get_tile_type() const
{
  return TILE_TYPE_SPRINGS;
}

std::string SpringsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SPRINGS;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpringsTile_test.cpp"
#endif
