#include "gtest/gtest.h"

TEST(SL_World_Ring, serialization_id)
{
  Ring ring;

  EXPECT_EQ(CLASS_ID_RING, ring.get_class_identifier());
}
