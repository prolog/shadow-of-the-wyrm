#include "gtest/gtest.h"

TEST(SL_World_Calendar, serialization_id)
{
  Calendar calendar;

  EXPECT_EQ(CLASS_ID_CALENDAR, calendar.get_class_identifier());
}

