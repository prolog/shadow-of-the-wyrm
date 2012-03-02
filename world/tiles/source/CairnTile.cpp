#include "CairnTile.hpp"

TileType CairnTile::get_tile_type() const
{
  return TILE_TYPE_CAIRN;
}

std::string CairnTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CAIRN;
}

#ifdef UNIT_TESTS
#include "unit_tests/CairnTile_test.cpp"
#endif
