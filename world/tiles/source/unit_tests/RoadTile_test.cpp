#include "gtest/gtest.h"

TEST(SL_World_Tiles_RoadTile, type_is_TILE_TYPE_ROAD)
{
  RoadTile road_tile;

  EXPECT_EQ(TILE_TYPE_ROAD, road_tile.get_tile_type());
}
