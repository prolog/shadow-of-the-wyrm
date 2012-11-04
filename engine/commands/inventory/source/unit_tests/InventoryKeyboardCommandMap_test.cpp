#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Inventory_InventoryKeyboardCommandMap, serialization_id)
{
  InventoryKeyboardCommandMap ikcm;

  EXPECT_EQ(CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP, ikcm.get_class_identifier());
}

