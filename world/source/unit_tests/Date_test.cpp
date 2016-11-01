#include "gtest/gtest.h"

TEST(SW_World_Date, get_time_of_day)
{
  Date night_date1(0, 3, 6, 1,1,1,1,1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_NIGHT, night_date1.get_time_of_day());

  Date night_date2(0,15,22,1,1,1,1,1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_NIGHT, night_date2.get_time_of_day());

  Date day_date1(0, 0, 7, 1, 1, 1, 1, 1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_DAY, day_date1.get_time_of_day());

  Date day_date2(0, 15, 16, 1, 1, 1, 1, 1);

  EXPECT_EQ(TimeOfDayType::TIME_OF_DAY_DAY, day_date2.get_time_of_day());
}