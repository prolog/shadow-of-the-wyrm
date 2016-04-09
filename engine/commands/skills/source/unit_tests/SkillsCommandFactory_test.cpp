#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Skills_SkillsCommandFactory, serialization_id)
{
  SkillsCommandFactory scf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILLS_COMMAND_FACTORY, scf.get_class_identifier());
}

