#include "gtest/gtest.h"

TEST(SL_Engine_Maps_CoordUtils, incr)
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

TEST(SL_Engine_Maps_CoordUtils, end_coordinate)
{
  EXPECT_TRUE(CoordUtils::is_end(CoordUtils::end()));
}

TEST(SL_Engine_Maps_CoordUtils, perimeter_coords)
{
  Coordinate top_left(1,1);
  Coordinate bottom_right(3,3);

  vector<Coordinate> coords = CoordUtils::get_perimeter_coordinates(top_left, bottom_right);

  // Are all the perimeter coordinates there?
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(1,1)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(1,2)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(1,3)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(2,3)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(3,3)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(3,2)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(3,1)) != coords.end());
  EXPECT_TRUE(std::find(coords.begin(), coords.end(), make_pair(2,1)) != coords.end());

  // Ensure no central coordinates are there.
  EXPECT_FALSE(std::find(coords.begin(), coords.end(), make_pair(2, 2)) != coords.end());
}

TEST(SL_Engine_Maps_CoordUtils, coords_in_range)
{
  Coordinate top_left(2,2);
  Coordinate bottom_right(7,7);

  vector<Coordinate> coords = CoordUtils::get_coordinates_in_range(top_left, bottom_right);

  for (int row = top_left.first; row <= bottom_right.first; row++)
  {
    for (int col = top_left.second; col <= bottom_right.second; col++)
    {
      Coordinate c = make_pair(row, col);
      EXPECT_TRUE(std::find(coords.begin(), coords.end(), c) != coords.end());
    }
  }
}

TEST(SL_Engine_Maps_CoordUtils, perimeter_length)
{
  Coordinate a(0,0);
  Coordinate b(10,10);

  EXPECT_EQ(40, CoordUtils::get_perimeter_length(a, b));

  a.first = 10;
  a.second = 15;
  b.first = 17;
  b.second = 17;

  EXPECT_EQ(18, CoordUtils::get_perimeter_length(a, b));
}

TEST(SL_Engine_Maps_CoordUtils, get_new_coordinate)
{
  Coordinate c(10, 10);
  Coordinate c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH_WEST);
  EXPECT_EQ(make_pair(9, 9), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH_WEST, 2);
  EXPECT_EQ(make_pair(8, 8), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH);
  EXPECT_EQ(make_pair(9, 10), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH, 3);
  EXPECT_EQ(make_pair(7, 10), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH_EAST);
  EXPECT_EQ(make_pair(9, 11), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH_EAST, 4);
  EXPECT_EQ(make_pair(6, 14), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_WEST);
  EXPECT_EQ(make_pair(10, 9), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_WEST, 5);
  EXPECT_EQ(make_pair(10, 5), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_EAST);
  EXPECT_EQ(make_pair(10, 11), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_EAST, 6);
  EXPECT_EQ(make_pair(10, 16), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH_WEST);
  EXPECT_EQ(make_pair(11, 9), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH_WEST, 2);
  EXPECT_EQ(make_pair(12, 8), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH);
  EXPECT_EQ(make_pair(11, 10), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH, 8);
  EXPECT_EQ(make_pair(18, 10), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH_EAST);
  EXPECT_EQ(make_pair(11, 11), c_new);

  c_new = CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH_EAST, 7);
  EXPECT_EQ(make_pair(17, 17), c_new);
}