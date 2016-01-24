#include "gtest/gtest.h"

#include <iostream>

TEST(SW_Engine_FieldOfView, BresenhamLine)
{
  BresenhamLine bl;

  vector<Coordinate> coords = bl.get_points_in_line(0, 0, 5, 0);

  Coordinate test_coord;
    
  for (int i = 0; i <= 5; i++)
  {
    test_coord.first = i;
    test_coord.second = 0;
    
    EXPECT_TRUE(find(coords.begin(), coords.end(), test_coord) != coords.end());
  }
  
  test_coord.first = 10;
  test_coord.second = 9;

  EXPECT_FALSE(find(coords.begin(), coords.end(), test_coord) != coords.end());
  
  coords = bl.get_points_in_line(3, 6, 7, 10);

  for (int i = 3; i <= 7; i++)
  {
    int j = i + 3;
    
    test_coord.first = i;
    test_coord.second = j;
    
    EXPECT_TRUE(find(coords.begin(), coords.end(), test_coord) != coords.end());
  }
}
