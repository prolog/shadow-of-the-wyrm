#include "WellTile.hpp"
#include "NullInventory.hpp"

WellTile::WellTile()
{
  items = std::make_shared<NullInventory>();

  // All wells lead down to a simple underground level.
  MapExitPtr me = std::make_shared<MapExit>();
  me->set_terrain_type(TileType::TILE_TYPE_WELL);
  map_exits[Direction::DIRECTION_DOWN] = me;
}

TileType WellTile::get_tile_type() const
{
  return TileType::TILE_TYPE_WELL;
}

std::string WellTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WELL;
}

Tile* WellTile::clone()
{
  return new WellTile(*this);
}

ClassIdentifier WellTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WELL_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/WellTile_test.cpp"
#endif
