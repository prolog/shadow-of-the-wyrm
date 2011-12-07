#include "gtest/gtest.h"

TEST(SL_Display_MapDisplayArea, default_width_and_height)
{
  MapDisplayArea default_area;

  EXPECT_EQ(0, static_cast<int>(default_area.get_width()));
  EXPECT_EQ(0, static_cast<int>(default_area.get_height()));
}

TEST(SL_Display_MapDisplayArea, set_width_and_height)
{
  MapDisplayArea display_area(20, 80);

  EXPECT_EQ(20, static_cast<int>(display_area.get_height()));
  EXPECT_EQ(80, static_cast<int>(display_area.get_width()));

  display_area.set_width(40);
  display_area.set_height(10);

  EXPECT_EQ(40, static_cast<int>(display_area.get_width()));
  EXPECT_EQ(10, static_cast<int>(display_area.get_height()));
}
