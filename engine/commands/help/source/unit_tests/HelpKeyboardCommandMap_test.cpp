#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Help_HelpKeyboardCommandMap, serialization_id)
{
  HelpKeyboardCommandMap hkcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_HELP_KEYBOARD_COMMAND_MAP, hkcm.get_class_identifier());
}
