#include "gtest/gtest.h"

TEST(SW_Engine_Maps_Tiles_TileItemTransform, serialization_id)
{
  TileItemTransform ti;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TILE_ITEM_TRANSFORM, ti.get_class_identifier());
}

TEST(SW_Engine_Maps_Tiles_TileItemTransform, saveload)
{
  TileItemTransform ti1(make_pair(1,2), "some_item", 1, 2);
  TileItemTransform ti2;

  ostringstream ss;
  ti1.serialize(ss);

  istringstream iss(ss.str());

  ti2.deserialize(iss);

  EXPECT_TRUE(ti1 == ti2);
}

