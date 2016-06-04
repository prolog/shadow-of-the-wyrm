#include "gtest/gtest.h"

TEST(SL_World_Engine_Commands_Skills_ShowSkillsCommandProcessor, can_process)
{
  CreaturePtr cp = std::make_shared<Creature>();
  CreaturePtr null_cp;

  ShowSkillsCommandProcessor sscp;

  EXPECT_FALSE(sscp.can_process(null_cp));

  EXPECT_FALSE(sscp.can_process(cp));

  cp->set_is_player(true, nullptr);

  EXPECT_TRUE(sscp.can_process(cp));
}
