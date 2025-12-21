#include "gtest/gtest.h"

TEST(SW_Engine_Calculator_BrewingCalculator, pct_chance_additional_potion)
{
  BrewingCalculator bc;

  EXPECT_EQ(0, bc.calc_pct_chance_additional_potion(nullptr));

  CreaturePtr c = std::make_shared<Creature>();
  std::vector<std::pair<int, int>> skill_and_expected = { {0, 0}, {1, 0}, {10, 2}, {27, 6}, {33, 8}, {50, 12}, {99, 24}, {100, 100} };

  for (const auto& sk_pair : skill_and_expected)
  {
    c->get_skills().set_value(SkillType::SKILL_GENERAL_BREWING, sk_pair.first);

    EXPECT_EQ(sk_pair.second, bc.calc_pct_chance_additional_potion(c));
  }

}

