#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Help_OrderKeyboardCommandMap, serialization_id)
{
  OrderKeyboardCommandMap okcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ORDER_KEYBOARD_COMMAND_MAP, okcm.get_class_identifier());
}
