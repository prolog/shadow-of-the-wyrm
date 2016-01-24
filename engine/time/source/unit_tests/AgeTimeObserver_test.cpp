#include "gtest/gtest.h"

TEST(SW_Engine_Time_AgeTimeObserver, serialization_id)
{
  AgeTimeObserver ato;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AGE_TIME_OBSERVER, ato.get_class_identifier());
}

