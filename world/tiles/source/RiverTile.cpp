#include "RiverTile.hpp"
#include "NullInventory.hpp"
#include "TileProperties.hpp"
#include "WaterTypes.hpp"

RiverTile::RiverTile()
{
  items = std::make_shared<NullInventory>();
  set_additional_property(TileProperties::TILE_PROPERTY_WATER_TYPE, std::to_string(static_cast<int>(WaterType::WATER_TYPE_FRESH)));
}

TileType RiverTile::get_tile_type() const
{
  return TileType::TILE_TYPE_RIVER;
}

TileSuperType RiverTile::get_tile_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
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
