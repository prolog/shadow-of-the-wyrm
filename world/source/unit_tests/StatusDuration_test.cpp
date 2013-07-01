#include "gtest/gtest.h"

TEST(SL_World_StatusDuration, serialization_id)
{
  StatusDuration sd;

  EXPECT_EQ(CLASS_ID_STATUS_DURATION, sd.get_class_identifier());
}
