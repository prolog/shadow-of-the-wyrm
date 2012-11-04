#include "gtest/gtest.h"

TEST(SL_Engine_Actions_ActionCoordinator, serialization_id)
{
  ActionCoordinator ac;

  EXPECT_EQ(CLASS_ID_ACTION_COORDINATOR, ac.get_class_identifier());
}

