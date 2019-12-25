#include "gtest/gtest.h"

TEST(SW_World_Tiles_Weather, weather_creation)
{
  Weather w("");

  EXPECT_EQ(0, w.get_wind_speed());

  Weather w2("36");

  EXPECT_EQ(36, w2.get_wind_speed());
}

TEST(SW_World_Tiles_Weather, setter_getter)
{
  Weather w("");
  w.set_wind_speed(46);

  EXPECT_EQ(46, w.get_wind_speed());
}
