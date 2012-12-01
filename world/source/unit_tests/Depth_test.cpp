#include "gtest/gtest.h"

TEST(SL_World_Depth, serialization_id)
{
  Depth depth;

  EXPECT_EQ(CLASS_ID_DEPTH, depth.get_class_identifier());
}

TEST(SL_World_Depth, saveload)
{
  Depth depth, depth2;

  depth.set_current(5);
  depth.set_maximum(56);

  ostringstream ss;

  depth.serialize(ss);

  istringstream iss(ss.str());

  depth2.deserialize(iss);

  EXPECT_TRUE(depth == depth2);
}