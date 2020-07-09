#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_BeastmasteryCalculator, calculate_pct_chance_tame)
{
  BeastmasteryCalculator bc;

  EXPECT_EQ(0, bc.calculate_pct_chance_tame(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();
  std::map<int, int> exp_vals = { {0,0}, {10,0}, {15,5}, {26,16}, {37,27}, {43,33}, {54,44}, {65,55},
                                  {77,67}, {88,78}, {99,89}, {100, 90} };

  for (auto v : exp_vals)
  {
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, v.first);
    EXPECT_EQ(v.second, bc.calculate_pct_chance_tame(creature));
  }
}
