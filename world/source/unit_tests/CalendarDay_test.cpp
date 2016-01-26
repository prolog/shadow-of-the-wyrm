#include "gtest/gtest.h"

TEST(SW_World_CalendarDay, serialization_id)
{
  CalendarDay cd;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CALENDAR_DAY, cd.get_class_identifier());
}

TEST(SW_World_CalendarDay, saveload)
{
  CalendarDay cd("bing", "asdf", 123);
  CalendarDay cd2;

  ostringstream ss;

  cd.serialize(ss);

  istringstream iss(ss.str());

  cd2.deserialize(iss);

  EXPECT_TRUE(cd == cd2);
}

