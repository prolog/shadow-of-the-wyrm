#include "VillageTile.hpp"

VillageTile::VillageTile()
: tile_subtype(TILE_TYPE_FIELD)
{
}

VillageTile::VillageTile(const TileType new_tile_subtype)
{
  tile_subtype = new_tile_subtype;
}

bool VillageTile::display_description_on_arrival() const
{
  return true;
}

TileType VillageTile::get_tile_type() const
{
  return TILE_TYPE_VILLAGE;
}

TileType VillageTile::get_tile_subtype() const
{
  return tile_subtype;
}

std::string VillageTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_VILLAGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/VillageTile_test.cpp"
#endif
