#include "gtest/gtest.h"

TEST(SW_Engine_Maps_CoordUtils, incr)
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

TEST(SW_Engine_Maps_CoordUtils, end_coordinate)
{
  EXPECT_TRUE(CoordUtils::is_end(CoordUtils::end()));
}

TEST(SW_Engine_Maps_CoordUtils, perimeter_coords)
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

TEST(SW_Engine_Maps_CoordUtils, coords_in_range)
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

TEST(SW_Engine_Maps_CoordUtils, perimeter_length)
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

TEST(SW_Engine_Maps_CoordUtils, get_new_coordinate)
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

TEST(SW_Engine_Maps_CoordUtils, are_segments_joinable_horizontal)
{
  int y_incr = 2;

  // Two parallel segments, horizontal, perfect overlap.
  pair<Coordinate, Coordinate> l1 = make_pair(make_pair(1,2), make_pair(3,2));
  pair<Coordinate, Coordinate> l2 = make_pair(make_pair(1,4), make_pair(3,4));

  auto result = CoordUtils::are_segments_joinable(l1, l2, y_incr);
  vector<Coordinate> expected = { {1,3}, {2,3}, {3,3} };

  EXPECT_TRUE(result.first);
  EXPECT_EQ(expected, result.second);

  // Two parallel segments, some overlap.
  l1 = make_pair(make_pair(1,2), make_pair(3,2));
  l2 = make_pair(make_pair(3,4), make_pair(5,4));

  result = CoordUtils::are_segments_joinable(l1, l2, y_incr);
  expected = { {3,3} };

  EXPECT_TRUE(result.first);
  EXPECT_EQ(expected, result.second);

  // Two parallel segments, no overlap.
  l1 = make_pair(make_pair(1, 2), make_pair(3, 2));
  l2 = make_pair(make_pair(1, 9), make_pair(5, 9));

  result = CoordUtils::are_segments_joinable(l1, l2, y_incr);
  expected.clear();

  EXPECT_FALSE(result.first);
  EXPECT_EQ(expected, result.second);

  // Two vertical segments, far apart.
  l1 = make_pair(make_pair(1, 2), make_pair(3, 2));
  l2 = make_pair(make_pair(12, 12), make_pair(15, 12));

  result = CoordUtils::are_segments_joinable(l1, l2, y_incr);
  expected.clear();

  EXPECT_FALSE(result.first);
  EXPECT_EQ(expected, result.second);
}

TEST(SW_Engine_Maps_CoordUtils, are_segments_joinable_vertical)
{
  int x_incr = 2;

  // Two parallel segments, vertical, perfect overlap
  pair<Coordinate, Coordinate> l1 = make_pair(make_pair(2, 5), make_pair(7, 5));
  pair<Coordinate, Coordinate> l2 = make_pair(make_pair(2, 3), make_pair(7, 3));

  auto result = CoordUtils::are_segments_joinable(l1, l2, x_incr);
  vector<Coordinate> expected = { {2,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4} };

  EXPECT_TRUE(result.first);
  EXPECT_EQ(expected, result.second);

  // Two parallel sections, some overlap
  l1 = make_pair(make_pair(2, 5), make_pair(7, 5));
  l2 = make_pair(make_pair(6, 3), make_pair(9, 3));

  result = CoordUtils::are_segments_joinable(l1, l2, x_incr);
  expected = { {6,4}, {7,4} };

  EXPECT_TRUE(result.first);
  EXPECT_EQ(expected, result.second);

  // Two parallel sections, no overlap
  l1 = make_pair(make_pair(2, 5), make_pair(7, 5));
  l2 = make_pair(make_pair(17, 3), make_pair(20, 3));

  result = CoordUtils::are_segments_joinable(l1, l2, x_incr);
  expected.clear();

  EXPECT_FALSE(result.first);
  EXPECT_EQ(expected, result.second);

  // Two non-parallel, no-overlap sections
  l1 = make_pair(make_pair(2, 5), make_pair(7, 5));
  l2 = make_pair(make_pair(19, 15), make_pair(30, 15));

  result = CoordUtils::are_segments_joinable(l1, l2, x_incr);
  expected.clear();

  EXPECT_FALSE(result.first);
  EXPECT_EQ(expected, result.second);

  // Failure case from early development - should actually overlap.
  l1 = make_pair(make_pair(1,5), make_pair(1,11));
  l2 = make_pair(make_pair(3,2), make_pair(3,25));

  result = CoordUtils::are_segments_joinable(l1, l2, x_incr);
  expected = { {2,5}, {2,6}, {2,7}, {2,8}, {2,9}, {2,10}, {2,11} };

  EXPECT_TRUE(result.first);
  EXPECT_EQ(expected, result.second);
}

TEST(SW_Engine_Maps_CoordUtils, are_coordinates_joinable)
{
  // Horizontally adjacent coordinates.
  Coordinate c1(1,1);
  Coordinate c2(1,2);
  Coordinate c3(1,3);
  int y_incr = 2;

  EXPECT_TRUE(CoordUtils::are_coordinates_joinable(c1, c3, y_incr).first);
  EXPECT_TRUE(CoordUtils::are_coordinates_joinable(c3, c1, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c1, c2, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c2, c3, y_incr).first);

  // Vertically adjacent coordinates.
  c1 = {3,3};
  c2 = {4,3};
  c3 = {5,3};

  EXPECT_TRUE(CoordUtils::are_coordinates_joinable(c1, c3, y_incr).first);
  EXPECT_TRUE(CoordUtils::are_coordinates_joinable(c3, c1, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c1, c2, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c2, c3, y_incr).first);

  // Diagonally-adjacent coordinates.
  c1 = {7,7};
  c2 = {8,8};
  c3 = {9,9};

  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c1, c3, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c3, c1, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c1, c2, y_incr).first);
  EXPECT_FALSE(CoordUtils::are_coordinates_joinable(c2, c3, y_incr).first);
}

TEST(SW_Engine_Maps_CoordUtils, ends_before)
{
  // Vertical segment
  pair<Coordinate, Coordinate> l1 = make_pair(make_pair(5, 3), make_pair(5, 5));
  pair<Coordinate, Coordinate> l2 = make_pair(make_pair(4, 3), make_pair(7, 3));

  EXPECT_FALSE(CoordUtils::ends_before(l1, l2));

  l1 = make_pair(make_pair(1,3), make_pair(3, 3));

  EXPECT_TRUE(CoordUtils::ends_before(l1, l2));

  // Horizontal segment
  l1 = make_pair(make_pair(1, 1), make_pair(1, 4));
  l2 = make_pair(make_pair(1, 3), make_pair(1, 7));

  EXPECT_FALSE(CoordUtils::ends_before(l1, l2));

  l2 = make_pair(make_pair(1, 9), make_pair(1, 12));

  EXPECT_TRUE(CoordUtils::ends_before(l1, l2));
}

TEST(SW_Engine_Maps_CoordUtils, starts_after)
{
  // ...
}

TEST(SW_Engine_Maps_CoordUtils, is_horizontal)
{
  pair<Coordinate, Coordinate> seg = make_pair(make_pair(1, 3), make_pair(1, 5));

  EXPECT_TRUE(CoordUtils::is_horizontal(seg));

  seg.second = make_pair(1, 9);

  EXPECT_TRUE(CoordUtils::is_horizontal(seg));

  seg.second = make_pair(2, 9);

  EXPECT_FALSE(CoordUtils::is_horizontal(seg));
}

TEST(SW_Engine_Maps_CoordUtils, is_vertical)
{
  pair<Coordinate, Coordinate> seg = make_pair(make_pair(3, 1), make_pair(5, 1));

  EXPECT_TRUE(CoordUtils::is_vertical(seg));

  seg.second = make_pair(9, 1);

  EXPECT_TRUE(CoordUtils::is_vertical(seg));

  seg.second = make_pair(9, 2);

  EXPECT_FALSE(CoordUtils::is_vertical(seg));
}

TEST(SW_Engine_Maps_CoordUtils, to_string)
{
  Coordinate c(5,10);
  string s = CoordUtils::to_string(c);

  EXPECT_EQ("(5,10)", s);
}

TEST(SW_Engine_Maps_CoordUtils, beam_coords_cardinal)
{
  vector<Direction> dirs = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH};

  for (const auto d : dirs)
  {
    vector<Coordinate> c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 1);
    vector<Coordinate> exp = { { 5,5 } };
    EXPECT_EQ(exp, c);

    c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 2);
    exp = { { 5,5 },{ 5,4 },{ 5,6 } };
    EXPECT_EQ(exp, c);
  }

  dirs = {Direction::DIRECTION_EAST, Direction::DIRECTION_WEST};

  for (const auto d : dirs)
  {
    vector<Coordinate> c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 1);
    vector<Coordinate> exp = { { 5,5 } };
    EXPECT_EQ(exp, c);

    c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 2);
    exp = { { 5,5 },{ 4,5 },{ 6,5 } };
    EXPECT_EQ(exp, c);
  }
}

TEST(SW_Engine_Maps_CoordUtils, beam_coords_ordinal)
{
  vector<Direction> dirs = {Direction::DIRECTION_NORTH_WEST, Direction::DIRECTION_NORTH_EAST, Direction::DIRECTION_SOUTH_WEST, Direction::DIRECTION_SOUTH_EAST};

  for (const auto d : dirs)
  {
    vector<Coordinate> c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 1);
    vector<Coordinate> exp = { { 5,5 } };
    EXPECT_EQ(exp, c);

    c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 2);
    exp = { { 5,5 },{ 4,5 },{ 6,5 } };
    EXPECT_EQ(exp, c);

    c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 4);
    exp = { { 5,5 },{ 4,5 },{ 6,5 },{ 3,5 },{ 7,5 },{ 2,5 },{ 8,5 }};
    EXPECT_EQ(exp, c);
  }
}

TEST(SW_Engine_Maps_CoordUtils, beam_coords_invalid)
{
  vector<Direction> dirs = { Direction::DIRECTION_UP, Direction::DIRECTION_DOWN, Direction::DIRECTION_NULL };

  for (const auto d : dirs)
  {
    vector<Coordinate> c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 1);
    vector<Coordinate> exp = { { 5,5 } };
    EXPECT_EQ(exp, c);

    c = CoordUtils::get_beam_coordinates(make_pair(5, 5), d, 2);
    EXPECT_EQ(exp, c);
  }
}