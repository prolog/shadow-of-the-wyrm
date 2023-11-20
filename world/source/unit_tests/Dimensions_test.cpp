#include "gtest/gtest.h"

TEST(SW_World_Dimensions, DefaultDimensions)
{
  Dimensions dimensions;

  int EXPECTED_Y = DEFAULT_DIMENSIONS_Y;
  int EXPECTED_X = DEFAULT_DIMENSIONS_X;

  int y = dimensions.get_y();
  int x = dimensions.get_x();

  EXPECT_EQ(EXPECTED_Y, y);
  EXPECT_EQ(EXPECTED_X, x);
}

TEST(SW_World_Dimensions, Accessors)
{
  Dimensions dimensions;

  dimensions.set_x(1);
  dimensions.set_y(2);

  EXPECT_EQ(1, dimensions.get_x());
  EXPECT_EQ(2, dimensions.get_y());
}

TEST(SW_World_Dimensions, serialization_id)
{
  Dimensions dim;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DIMENSIONS, dim.get_class_identifier());
}

TEST(SW_World_Dimensions, contains)
{
  Dimensions dim;

  for (int y = -1; y < DEFAULT_DIMENSIONS_Y + 1; y++)
  {
    for (int x = -1; x < DEFAULT_DIMENSIONS_X + 1; x++)
    {
      bool exp_val = (y >= 0 && y <= (DEFAULT_DIMENSIONS_Y - 1) && x >= 0 && x <= (DEFAULT_DIMENSIONS_X - 1));
      EXPECT_EQ(exp_val, dim.contains({ y,x }));
    }
  }
}