#include "gtest/gtest.h"

TEST(SW_World_Tiles_Weather, equality)
{
  Weather w("55");
  Weather w2("");

  EXPECT_FALSE(w == w2);

  w2.set_wind_speed(55);

  EXPECT_TRUE(w == w2);
}

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

TEST(SW_World_Tiles_Weather, serialization_id)
{
  Weather w("");
  EXPECT_EQ(ClassIdentifier::CLASS_ID_WEATHER, w.get_class_identifier());
}

TEST(SW_World_Tiles_Weather, saveload)
{
  Weather w("32");
  ostringstream ss;

  w.serialize(ss);
  istringstream iss(ss.str());
  Weather w2("");
  w2.deserialize(iss);

  EXPECT_EQ(32, w2.get_wind_speed());
}
