#include "RiverTile.hpp"
#include "TileProperties.hpp"
#include "WaterInventory.hpp"
#include "WaterTypes.hpp"

RiverTile::RiverTile()
{
  items = std::make_shared<WaterInventory>();
}

TileType RiverTile::get_tile_type() const
{
  return TileType::TILE_TYPE_RIVER;
}

TileSuperType RiverTile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
}

WaterType RiverTile::get_water_type() const
{
  return WaterType::WATER_TYPE_FRESH;
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
