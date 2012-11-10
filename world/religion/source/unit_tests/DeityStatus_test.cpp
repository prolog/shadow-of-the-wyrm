#include "gtest/gtest.h"

TEST(SL_World_Religion_DeityStatus, serialization_id)
{
  DeityStatus ds;

  EXPECT_EQ(CLASS_ID_DEITY_STATUS, ds.get_class_identifier());
}

