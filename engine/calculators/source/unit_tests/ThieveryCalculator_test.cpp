#include "gtest/gtest.h"

TEST(SL_World_Calculators_ThieveryCalculator, pct_chance_steal)
{
  ThieveryCalculator tc;
  CreaturePtr steal = std::make_shared<Creature>();
  Statistic dex(18);
  steal->set_dexterity(dex);
  steal->get_skills().set_value(SkillType::SKILL_GENERAL_THIEVERY, 41);

  CreaturePtr target = std::make_shared<Creature>();
  Statistic agi(22);
  target->set_agility(agi);

  // 0 if either shared_ptr is null
  EXPECT_EQ(0, tc.calculate_pct_chance_steal(steal, nullptr));
  EXPECT_EQ(0, tc.calculate_pct_chance_steal(nullptr, target));
  EXPECT_EQ(0, tc.calculate_pct_chance_steal(nullptr, nullptr));

  // If not blind, score should be thievery + dex - agi.
  EXPECT_EQ(37, tc.calculate_pct_chance_steal(steal, target));

  // If target is blind, the above * 4.
  target->set_status("_blind", {"_blind", true, 1, ""});
  EXPECT_EQ(100, tc.calculate_pct_chance_steal(steal, target));
}

