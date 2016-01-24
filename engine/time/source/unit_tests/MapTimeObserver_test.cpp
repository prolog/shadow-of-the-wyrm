#include "gtest/gtest.h"

TEST(SW_Engine_Time_MapTimeObserver, serialization_id)
{
  MapTimeObserver mto;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAP_TIME_OBSERVER, mto.get_class_identifier());
}

