#include "RiverTile.hpp"
#include "NullInventory.hpp"

RiverTile::RiverTile()
{
  items = std::make_shared<NullInventory>();
}

TileType RiverTile::get_tile_type() const
{
  return TILE_TYPE_RIVER;
}

TileSuperType RiverTile::get_tile_super_type() const
{
  return TILE_SUPER_TYPE_WATER;
}

std::string RiverTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_RIVER;
}

Tile* RiverTile::clone()
{
  return new RiverTile(*this);
}

ClassIdentifier RiverTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_RIVER_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/RiverTile_test.cpp"
#endif
