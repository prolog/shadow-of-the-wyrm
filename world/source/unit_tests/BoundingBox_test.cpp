#include "gtest/gtest.h"

TEST(SW_World_BoundingBox, create)
{
  BoundingBox bb;

  Coordinate null_c = make_pair(-1, -1);
  EXPECT_EQ(null_c, bb.get_c1());
  EXPECT_EQ(null_c, bb.get_c2());

  Coordinate c1 = make_pair(5,5);
  Coordinate c2 = make_pair(7,8);
  BoundingBox bb2(c1, c2);

  EXPECT_EQ(c1, bb2.get_c1());
  EXPECT_EQ(c2, bb2.get_c2());
}

TEST(SW_World_BoundingBox, equals)
{
  BoundingBox nbb;
  BoundingBox nbb2(make_pair(-1,-1), make_pair(-1,-1));

  EXPECT_TRUE(nbb == nbb2);

  BoundingBox bb(make_pair(3,3), make_pair(4, 4));
  BoundingBox bb2(make_pair(5,5), make_pair(6,6));

  EXPECT_FALSE(bb == bb2);
  EXPECT_TRUE(bb2 == bb2);
}
