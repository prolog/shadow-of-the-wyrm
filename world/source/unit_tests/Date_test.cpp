#include "gtest/gtest.h"

TEST(SW_World_Date, get_class_identifier)
{
  Date d(1, 2, 3, 4, 5, 6, 6, 7);
  EXPECT_EQ(ClassIdentifier::CLASS_ID_DATE, d.get_class_identifier());
}

TEST(SW_World_Date, saveload)
{
  Date d(1, 2, 3, 4, 5, 6, 6, 7);
  Date d2(2, 23, 33, 44, 55, 66, 86, 97);
  ostringstream ss;

  d.serialize(ss);
  istringstream iss(ss.str());
  d2.deserialize(iss);

  EXPECT_EQ(d, d2);
}

TEST(SW_World_Date, get_time_of_day)
{
  Date night_date1(0, 3, 6, 1,1,1,1,1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_NIGHT, night_date1.get_time_of_day());

  Date night_date2(0,15,22,1,1,1,1,1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_NIGHT, night_date2.get_time_of_day());

  Date day_date1(0, 0, 7, 1, 1, 1, 1, 1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_DAWN, day_date1.get_time_of_day());

  Date day_date2(0, 15, 19, 1, 1, 1, 1, 1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_DUSK, day_date2.get_time_of_day());
}

TEST(SW_World_Date, get_days_equal)
{
  Date d(0, 0, 12, 1, 1, 333, 6, 832);
  Date d2(5, 4, 3, 1, 1, 333, 6, 832);
  Date d3(5, 4, 3, 1, 1, 331, 6, 832);
  Date d4(5, 4, 3, 1, 1, 222, 6, 834);

  EXPECT_TRUE(d.get_days_equal(d2));
  EXPECT_FALSE(d.get_days_equal(d3));
  EXPECT_FALSE(d.get_days_equal(d4));
}
