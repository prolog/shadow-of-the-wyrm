#include "gtest/gtest.h"

TEST(SW_World_Tiles_SewerComplexTile, type_is_TILE_TYPE_SEWER_COMPLEX)
{
  SewerComplexTile sewer_complex_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SEWER_COMPLEX, sewer_complex_tile.get_tile_type());
}

TEST(SW_World_Tiles_SewerComplexTile, tile_description_sid)
{
  SewerComplexTile sewer_complex_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_SEWER_COMPLEX, sewer_complex_tile.get_tile_description_sid());
}

TEST(SW_World_Tiles_SewerComplexTile, serialization_id)
{
  SewerComplexTile sewer_complex_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SEWER_COMPLEX_TILE, sewer_complex_tile.get_class_identifier());
}


