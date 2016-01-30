#include "gtest/gtest.h"

TEST(SW_Engine_Time_SpecialDayObserver, serialization_id)
{
  SpecialDayObserver sd;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SPECIAL_DAY_OBSERVER, sd.get_class_identifier());
}

