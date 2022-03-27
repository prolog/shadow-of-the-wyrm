#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_StealthCalculator, calculate_pct_chance_sneak_attack)
{
  StealthCalculator sc;

  EXPECT_EQ(0, sc.calculate_pct_chance_sneak_attack(nullptr, nullptr));

  CreaturePtr c = std::make_shared<Creature>();
  std::map<int, int> pct_chance_vals = {{0,0}, {7,1}, {11,2}, {46,9}};

  for (const auto& val_pair : pct_chance_vals)
  {
    c->get_skills().set_value(SkillType::SKILL_GENERAL_STEALTH, val_pair.first);
    EXPECT_EQ(val_pair.second, sc.calculate_pct_chance_sneak_attack(c, c));
  }

  CreaturePtr c2 = std::make_shared<Creature>();
  c->set_speed(40);
  c2->set_speed(50);

  pct_chance_vals = { {0, 20}, {7,21}, {11, 22}, {46, 29} };

  for (const auto& val_pair : pct_chance_vals)
  {
    c->get_skills().set_value(SkillType::SKILL_GENERAL_STEALTH, val_pair.first);
    EXPECT_EQ(val_pair.second, sc.calculate_pct_chance_sneak_attack(c, c2));
  }

  c2->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_BACKSTABBED, std::to_string(true));

  EXPECT_EQ(0, sc.calculate_pct_chance_sneak_attack(c, c2));
}
