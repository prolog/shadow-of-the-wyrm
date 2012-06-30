#include "SpringsTile.hpp"

TileType SpringsTile::get_tile_type() const
{
  return TILE_TYPE_SPRINGS;
}

TileSuperType SpringsTile::get_tile_super_type() const
{
  return TILE_SUPER_TYPE_WATER;
}

std::string SpringsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SPRINGS;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpringsTile_test.cpp"
#endif
