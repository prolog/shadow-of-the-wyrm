#include "SeaTile.hpp"
#include "NullInventory.hpp"
#include "WaterTypes.hpp"

SeaTile::SeaTile()
{
  items = std::make_shared<NullInventory>();
  set_additional_property(TileProperties::TILE_PROPERTY_WATER_TYPE, std::to_string(static_cast<int>(WaterType::WATER_TYPE_SALT)));
}

TileType SeaTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SEA;
}

TileSuperType SeaTile::get_tile_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
}

std::string SeaTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SEA;
}

Tile* SeaTile::clone()
{
  return new SeaTile(*this);
}

ClassIdentifier SeaTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SEA_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SeaTile_test.cpp"
#endif
