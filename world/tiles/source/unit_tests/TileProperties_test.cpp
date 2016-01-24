#include "gtest/gtest.h"

TEST(SW_World_Tiles_TileProperties, depth_custom_map_id)
{
  EXPECT_EQ("-3_CUSTOM_MAP_ID", TileProperties::get_depth_custom_map_id(-3));
  EXPECT_EQ("29_CUSTOM_MAP_ID", TileProperties::get_depth_custom_map_id(29));
}

TEST(SW_World_Tiles_TileProperties, is_depth_custom_map_id)
{
  EXPECT_EQ(false, TileProperties::is_depth_custom_map_id("PREVIOUS_MAP_ID")); // this one caused a lot of fun in the ID!
  EXPECT_EQ(true, TileProperties::is_depth_custom_map_id("-3_CUSTOM_MAP_ID"));
  EXPECT_EQ(false, TileProperties::is_depth_custom_map_id("ffdsafdsafdsa"));
}


