#include "gtest/gtest.h"
#include <algorithm>

class CellularAutomataGeneratorTest
{
  public:
    vector<pair<int, int>> get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col) { return CoordUtils::get_adjacent_map_coordinates(dim, row, col); }
};

TEST(SL_Engine_Generators_CellularAutomataGenerator, adjacent_map_coordinates_size)
{
  Dimensions d; // default dimensions;

  // North west
  int row  = 0;
  int col  = 0;
  vector<pair<int, int>> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  unsigned int expected_size = 3; // (0,1), (1,1), (1,0)
  unsigned int size = adjacent_coords.size();
  EXPECT_EQ(expected_size, size);

  row = 1;
  col = 0;
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  expected_size = 5; // (0, 0), (0, 1), (1, 1), (2, 1), (2, 0)
  size = adjacent_coords.size();
  EXPECT_EQ(expected_size, size);

  // Centre
  row = 10;
  col = 10;
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  expected_size = 8; // All neighbours
  size = adjacent_coords.size();
  EXPECT_EQ(expected_size, size);

  // South east
  row = (d.get_y() - 1);
  col = (d.get_x() - 1);
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  expected_size = 3;
  size = adjacent_coords.size();
  EXPECT_EQ(expected_size, size);
}

TEST(SL_Engine_Generators_Generator, adjacent_map_coordinates_content)
{
  Dimensions d; // default dimensions;

  // North west
  int row  = 0;
  int col  = 0;
  vector<pair<int, int>> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);

  pair<int,int> coords = make_pair(0,1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(1, 1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(1, 0);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());

  // NE
  row = 0;
  col = d.get_x() - 1;
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  coords = make_pair(0, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(1, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(1, col);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());

  // Centre
  row = 10;
  col = 10;
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  coords = make_pair(row-1, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row-1, col);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row-1, col+1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row, col+1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row+1, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row+1, col);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row+1, col+1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());

  // SW
  row = d.get_y() - 1;
  col = 0;
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  coords = make_pair(row-1, col);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row-1, col+1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row, col+1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());

  // SE
  row = d.get_y() - 1;
  col = d.get_x() - 1;
  adjacent_coords = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  coords = make_pair(row-1, col);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row-1, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());
  coords = make_pair(row, col-1);
  EXPECT_TRUE(find(adjacent_coords.begin(), adjacent_coords.end(), coords) != adjacent_coords.end());


}
