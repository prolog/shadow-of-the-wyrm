#include "gtest/gtest.h"

TEST(SL_Engine_Time_CreatureTimeObserver, serialization_id)
{
  CreatureTimeObserver cto;

  EXPECT_EQ(CLASS_ID_CREATURE_TIME_OBSERVER, cto.get_class_identifier());
}

