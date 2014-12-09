#include "gtest/gtest.h"

TEST(SL_Engine_Time_MapTimeObserver, serialization_id)
{
  MapTimeObserver mto;

  EXPECT_EQ(CLASS_ID_MAP_TIME_OBSERVER, mto.get_class_identifier());
}

