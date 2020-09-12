#include "gtest/gtest.h"

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
