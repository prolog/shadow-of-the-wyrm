#include "gtest/gtest.h"

TEST(SW_World_Calendar, serialization_id)
{
  Calendar calendar;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CALENDAR, calendar.get_class_identifier());
}

TEST(SW_World_Calendar, saveload)
{
  Calendar c, c2;
  ostringstream ss;

  c.serialize(ss);

  istringstream iss(ss.str());

  c2.deserialize(iss);

  EXPECT_TRUE(c == c2);
}
