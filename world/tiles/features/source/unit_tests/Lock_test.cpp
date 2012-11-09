#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Lock, serialization_id)
{
  Lock lock;

  EXPECT_EQ(CLASS_ID_LOCK, lock.get_class_identifier());
}

