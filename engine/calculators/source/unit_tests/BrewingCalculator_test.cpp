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

TEST(SW_Engine_Calculator_BrewingCalculator, pct_chance_each_status)
{
  CreaturePtr creature = std::make_shared<Creature>();
  map<ItemStatus, int> expected = { {ItemStatus::ITEM_STATUS_CURSED, 100}, {ItemStatus::ITEM_STATUS_UNCURSED, 0}, {ItemStatus::ITEM_STATUS_BLESSED, 0} };

  BrewingCalculator bc;
  auto statuses = bc.calc_item_status_pct_chance(nullptr);

  for (const auto& e_pair : expected)
  {
    EXPECT_EQ(e_pair.second, statuses[e_pair.first]);
  }

  map<int, map<ItemStatus, int>> skill_and_vals = { {1,  {{ItemStatus::ITEM_STATUS_CURSED, 100},
                                                          {ItemStatus::ITEM_STATUS_UNCURSED, 1},
                                                          {ItemStatus::ITEM_STATUS_BLESSED, 1}}},
                                                    {10, {{ItemStatus::ITEM_STATUS_CURSED, 100},
                                                          {ItemStatus::ITEM_STATUS_UNCURSED, 10},
                                                          {ItemStatus::ITEM_STATUS_BLESSED, 10}}} };

  for (const auto& sk_pair : skill_and_vals)
  {
    creature->get_skills().set_value(SkillType::SKILL_GENERAL_BREWING, sk_pair.first);
    expected = sk_pair.second;

    for (const auto& e_pair : expected)
    {
      statuses = bc.calc_item_status_pct_chance(creature);
      EXPECT_EQ(e_pair.second, statuses[e_pair.first]);
    }
  }
}

