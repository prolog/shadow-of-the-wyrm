#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Skills_SkillsCommandProcessorFactory, not_null)
{
  std::vector<SkillsSelectionType> sst_v = {SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL, SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL};

  for (const auto st : sst_v)
  {
    ISkillsCommandProcessorPtr scp = SkillsCommandProcessorFactory::create(st);

    EXPECT_TRUE(scp != nullptr);
  }
}

