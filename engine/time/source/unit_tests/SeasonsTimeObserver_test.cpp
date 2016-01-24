#include "gtest/gtest.h"

TEST(SW_Engine_Time_SeasonsTimeObserver, serialization_id)
{
  SeasonsTimeObserver sto;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SEASONS_TIME_OBSERVER, sto.get_class_identifier());
}

