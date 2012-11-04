#include "gtest/gtest.h"

TEST(SL_Engine_Time_SeasonsTimeObserver, serialization_id)
{
  SeasonsTimeObserver sto;

  EXPECT_EQ(CLASS_ID_SEASONS_TIME_OBSERVER, sto.get_class_identifier());
}

