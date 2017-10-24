#include "gtest/gtest.h"

TEST(SW_World_Tiles_MarshTile, type_is_TILE_TYPE_MARSH)
{
  MarshTile marsh_tile;

  EXPECT_EQ(TileType::TILE_TYPE_MARSH, marsh_tile.get_tile_type());
}

TEST(SW_World_Tiles_MarshTile, tile_super_type)
{
  MarshTile mt;

  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_GROUND, mt.get_tile_super_type());
}

TEST(SW_World_Tiles_MarshTile, tile_super_type_submerged)
{
  MarshTile mt;
  mt.set_submerged(true);

  EXPECT_EQ(TileSuperType::TILE_SUPER_TYPE_WATER, mt.get_tile_super_type());
}

TEST(SW_World_Tiles_MarshTile, serialization_id)
{
  MarshTile marsh_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MARSH_TILE, marsh_tile.get_class_identifier());
}

