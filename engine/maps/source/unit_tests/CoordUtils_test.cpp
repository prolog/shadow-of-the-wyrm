#include "gtest/gtest.h"

TEST(SL_Engine_CoordUtils, incr)
{
  Dimensions d; // Bog standard 20x80.
  Coordinate c(0, 0);
  Coordinate cprime(0, 1);

  EXPECT_EQ(cprime, CoordUtils::incr(c, d));

  c.second = 79;
  cprime.first = 1;
  cprime.second = 0;

  EXPECT_EQ(cprime, CoordUtils::incr(c, d));

  c.first = 19;
  c.second = 79;

  EXPECT_EQ(CoordUtils::end(), CoordUtils::incr(c, d));
}

TEST(SL_Engine_CoordUtils, end_coordinate)
{
  EXPECT_TRUE(CoordUtils::is_end(CoordUtils::end()));
}

TEST(SL_Engine_CoordUtils, perimeter_coords)
{
  Coordinate top_left(1,1);
  Coordinate bottom_right(3,3);

  set<Coordinate> coords = CoordUtils::get_perimeter_coordinates(top_left, bottom_right);

  // Are all the perimeter coordinates there?
  EXPECT_TRUE(coords.find(make_pair(1,1)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(1,2)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(1,3)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(2,3)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(3,3)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(3,2)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(3,1)) != coords.end());
  EXPECT_TRUE(coords.find(make_pair(2,1)) != coords.end());

  // Ensure no central coordinates are there.
  EXPECT_FALSE(coords.find(make_pair(2, 2)) != coords.end());
}

TEST(SL_Engine_CoordUtils, coords_in_range)
{
  Coordinate top_left(2,2);
  Coordinate bottom_right(7,7);

  set<Coordinate> coords = CoordUtils::get_coordinates_in_range(top_left, bottom_right);

  for (int row = top_left.first; row <= bottom_right.first; row++)
  {
    for (int col = top_left.second; col <= bottom_right.second; col++)
    {
      Coordinate c = make_pair(row, col);
      EXPECT_TRUE(coords.find(c) != coords.end());
    }
  }
}