#include "gtest/gtest.h"

TEST(SL_World_Tiles_RoadTile, type_is_TILE_TYPE_ROAD)
{
  RoadTile road_tile;

  EXPECT_EQ(TILE_TYPE_ROAD, road_tile.get_tile_type());
}

TEST(SL_World_Tiles_RoadTile, serialization_id)
{
  RoadTile road_tile;

  EXPECT_EQ(CLASS_ID_ROAD_TILE, road_tile.get_class_identifier());
}
