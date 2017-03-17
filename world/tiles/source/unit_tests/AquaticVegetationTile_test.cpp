#include "gtest/gtest.h"

TEST(SW_World_Tiles_AquaticVegetationTile, type_is_TILE_TYPE_AQUATIC_VEGETATION)
{
  AquaticVegetationTile av_tile;

  EXPECT_EQ(TileType::TILE_TYPE_AQUATIC_VEGETATION, av_tile.get_tile_type());
}

TEST(SW_World_Tiles_AquaticVegetationTile, tile_super_type)
{
  AquaticVegetationTile av_tile;

  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_WATER, av_tile.get_tile_super_type());
}

TEST(SW_World_Tiles_AquaticVegetationTile, serialization_id)
{
  AquaticVegetationTile av_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AQUATIC_VEGETATION_TILE, av_tile.get_class_identifier());
}

