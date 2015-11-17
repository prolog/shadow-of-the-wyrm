#include "gtest/gtest.h"

TEST(SL_Engine_Maps_Tiles_TileTransform, serialization_id)
{
  TileTransform tt;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TILE_TRANSFORM, tt.get_class_identifier());
}

TEST(SL_Engine_Maps_Tiles_TileTransform, saveload)
{
  TileTransform tt1(make_pair(1,2), TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_FIELD, {{"anc", "1"}, {"fdsa", "2"}});
  TileTransform tt2;

  ostringstream ss;
  tt1.serialize(ss);

  istringstream iss(ss.str());

  tt2.deserialize(iss);

  EXPECT_TRUE(tt1 == tt2);
}

