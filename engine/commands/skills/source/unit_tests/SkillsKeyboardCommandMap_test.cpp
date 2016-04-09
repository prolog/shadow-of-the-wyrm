#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Skills_SkillsKeyboardCommandMap, serialization_id)
{
  SkillsKeyboardCommandMap skcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILLS_KEYBOARD_COMMAND_MAP, skcm.get_class_identifier());
}

