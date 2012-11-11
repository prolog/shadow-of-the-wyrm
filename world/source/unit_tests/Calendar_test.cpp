#include "gtest/gtest.h"

TEST(SL_World_Calendar, serialization_id)
{
  Calendar calendar;

  EXPECT_EQ(CLASS_ID_CALENDAR, calendar.get_class_identifier());
}

TEST(SL_World_Calendar, saveload)
{
  Calendar c, c2;
  ostringstream ss;

  c.serialize(ss);

  istringstream iss(ss.str());

  c2.deserialize(iss);

  EXPECT_TRUE(c == c2);
}
