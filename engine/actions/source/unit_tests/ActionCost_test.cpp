#include "gtest/gtest.h"

TEST(SL_Engine_Actions_ActionCost, serialization_id)
{
  ActionCost ac;

  EXPECT_EQ(CLASS_ID_ACTION_COST, ac.get_class_identifier());
}

