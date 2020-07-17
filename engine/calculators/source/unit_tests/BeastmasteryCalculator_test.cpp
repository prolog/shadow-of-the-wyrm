#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_BeastmasteryCalculator, calculate_pct_chance_tame)
{
  BeastmasteryCalculator bc;

  EXPECT_EQ(0, bc.calculate_pct_chance_tame(nullptr, nullptr));

  CreaturePtr creature = std::make_shared<Creature>();
  CreaturePtr to_tame = std::make_shared<Creature>();

  EXPECT_EQ(0, bc.calculate_pct_chance_tame(creature, nullptr));
  EXPECT_EQ(0, bc.calculate_pct_chance_tame(nullptr, to_tame));

  std::map<int, int> exp_vals = { {0,0}, {10,0}, {15,5}, {26,16}, {37,27}, {43,33}, {54,44}, {65,55},
                                  {77,67}, {88,78}, {99,80}, {100, 80} };

  for (auto v : exp_vals)
  {
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, v.first);
    EXPECT_EQ(v.second, bc.calculate_pct_chance_tame(creature, to_tame));
  }

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, 50);
  creature->set_level(11);
  to_tame->set_level(1);

  EXPECT_EQ(50, bc.calculate_pct_chance_tame(creature, to_tame));
  
  creature->set_level(1);
  to_tame->set_level(11);

  EXPECT_EQ(30, bc.calculate_pct_chance_tame(creature, to_tame));
}

TEST(SW_Engine_Calculators_BeastmasteryCalculator, calculate_exp_proportion)
{
  BeastmasteryCalculator bc;
  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_DOUBLE_EQ(0.0, bc.calculate_exp_proportion(nullptr));
  EXPECT_DOUBLE_EQ(0.0, bc.calculate_exp_proportion(creature));

  for (int i = 1; i <= 100; i++)
  {
    double exp_val = static_cast<double>(i) / 100.0;
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, i);

    EXPECT_DOUBLE_EQ(exp_val, bc.calculate_exp_proportion(creature));
  }
}