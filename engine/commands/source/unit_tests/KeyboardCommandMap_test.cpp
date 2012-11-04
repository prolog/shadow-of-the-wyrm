#include "gtest/gtest.h"

TEST(SL_Engine_Commands_KeyboardCommandMap, serialization_id)
{
  KeyboardCommandMap kcm;

  EXPECT_EQ(CLASS_ID_KEYBOARD_COMMAND_MAP, kcm.get_class_identifier());
}
