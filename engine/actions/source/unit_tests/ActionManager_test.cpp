#include "gtest/gtest.h"

TEST(SL_Engine_Actions_ActionManager, serialization_id)
{
  ActionManager am;

  EXPECT_EQ(CLASS_ID_ACTION_MANAGER, am.get_class_identifier());
}

