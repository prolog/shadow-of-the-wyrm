#include "gtest/gtest.h"

TEST(SL_Engine_Generators_TileDepthOptions, default_values)
{
  TileDepthOptions tdo;
  std::vector<int> empty;

  EXPECT_EQ(1, tdo.get_min_depth());
  EXPECT_EQ(1, tdo.get_max_depth());
  EXPECT_TRUE(empty == tdo.get_remaining_depths());

  TileDepthOptions tdo2(6, 7, { 8, 9, 10 });
  vector<int> expected = { 8,9,10 };

  EXPECT_EQ(6, tdo2.get_min_depth());
  EXPECT_EQ(7, tdo2.get_max_depth());
  EXPECT_TRUE(expected == tdo2.get_remaining_depths());
}

TEST(SL_Engine_Generators_TileDepthOptions, set_and_get_values)
{
  TileDepthOptions tdo;

  tdo.set_min_depth(12);
  tdo.set_max_depth(50);
  tdo.set_remaining_depths({ 1,2,3 });

  vector<int> expected = { 1,2,3 };

  EXPECT_EQ(12, tdo.get_min_depth());
  EXPECT_EQ(50, tdo.get_max_depth());
  EXPECT_EQ(expected, tdo.get_remaining_depths());

  vector<int>& depths = tdo.get_remaining_depths_ref();
  depths.clear();

  depths = { 50, 40, 30 };
  expected = depths;

  EXPECT_TRUE(expected == tdo.get_remaining_depths());
}
