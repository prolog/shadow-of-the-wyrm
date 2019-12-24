#include "gtest/gtest.h"

TEST(SW_World_Tiles_Weather, weather_creation)
{
  Weather w("");

  EXPECT_EQ(0, w.get_wind_speed());

  Weather w2("36");

  EXPECT_EQ(36, w2.get_wind_speed());
}

