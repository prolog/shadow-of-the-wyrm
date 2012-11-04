#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Equipment_EquipmentKeyboardCommandMap, serialization_id)
{
  EquipmentKeyboardCommandMap ekcm;

  EXPECT_EQ(CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP, ekcm.get_class_identifier());
}

