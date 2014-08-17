#include "gtest/gtest.h"

TEST(SL_World_Tiles_TileProperties, depth_custom_map_id)
{
  EXPECT_EQ("-3_MAP_ID", TileProperties::get_depth_custom_map_id(-3));
  EXPECT_EQ("29_MAP_ID", TileProperties::get_depth_custom_map_id(29));
}

