#include "gtest/gtest.h"

TEST(SL_World_Religion_Religion, serialization_id)
{
  Religion r;

  EXPECT_EQ(CLASS_ID_RELIGION, r.get_class_identifier());
}
