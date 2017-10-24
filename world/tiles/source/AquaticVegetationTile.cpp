#include "AquaticVegetationTile.hpp"
#include "WaterTypes.hpp"

AquaticVegetationTile::AquaticVegetationTile()
{
}

TileType AquaticVegetationTile::get_tile_type() const
{
  return TileType::TILE_TYPE_AQUATIC_VEGETATION;
}

TileSuperType AquaticVegetationTile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
}

WaterType AquaticVegetationTile::get_water_type() const
{
  return WaterType::WATER_TYPE_SALT;
}

std::string AquaticVegetationTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_AQUATIC_VEGETATION;
}

Tile* AquaticVegetationTile::clone()
{
  return new AquaticVegetationTile(*this);
}

ClassIdentifier AquaticVegetationTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AQUATIC_VEGETATION_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/AquaticVegetationTile_test.cpp"
#endif

