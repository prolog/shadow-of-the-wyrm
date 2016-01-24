#include "gtest/gtest.h"

TEST(SW_Engine_Time_WorldTimeKeeper, serialization_id)
{
  WorldTimeKeeper wtk;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WORLD_TIME_KEEPER, wtk.get_class_identifier());
}

