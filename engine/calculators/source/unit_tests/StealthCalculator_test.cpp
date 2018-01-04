#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_StealthCalculator, calculate_pct_chance_sneak_attack)
{
  StealthCalculator sc;

  EXPECT_EQ(0, sc.calculate_pct_chance_sneak_attack(nullptr));

  CreaturePtr c = std::make_shared<Creature>();
  std::map<int, int> pct_chance_vals = {{0,0}, {7,1}, {11,1}, {46,4}};

  for (const auto& val_pair : pct_chance_vals)
  {
    c->get_skills().set_value(SkillType::SKILL_GENERAL_STEALTH, val_pair.first);
    EXPECT_EQ(val_pair.second, sc.calculate_pct_chance_sneak_attack(c));
  }
}
