#include "SeabedTile.hpp"
#include "WaterTypes.hpp"

SeabedTile::SeabedTile()
{
}

TileType SeabedTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SEABED;
}

TileSuperType SeabedTile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
}

WaterType SeabedTile::get_water_type() const
{
  return WaterType::WATER_TYPE_SALT;
}

std::string SeabedTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SEABED;
}

Tile* SeabedTile::clone()
{
  return new SeabedTile(*this);
}

ClassIdentifier SeabedTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SEABED_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SeabedTile_test.cpp"
#endif

