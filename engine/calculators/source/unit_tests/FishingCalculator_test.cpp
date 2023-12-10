#include "gtest/gtest.h"
#include "MiscItem.hpp"

TEST(SOTW_Engine_Calculators_FishingCalculator, calculate_fishing_outcomes)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;
  vector<pair<FishingOutcomeType, int>> exp_outcomes;
  FishingCalculator fc;

  exp_outcomes = {{FishingOutcomeType::FISHING_OUTCOME_CATCH, 1},
                  {FishingOutcomeType::FISHING_OUTCOME_NIBBLE, 0},
                  {FishingOutcomeType::FISHING_OUTCOME_ESCAPE, 0},
                  {FishingOutcomeType::FISHING_OUTCOME_NO_CATCH, 100}};

  EXPECT_EQ(exp_outcomes, fc.calculate_fishing_outcomes(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FISHING, 25);
  creature->set_skills(skills);

  exp_outcomes = {{FishingOutcomeType::FISHING_OUTCOME_CATCH, 12},
                  {FishingOutcomeType::FISHING_OUTCOME_NIBBLE, 8},
                  {FishingOutcomeType::FISHING_OUTCOME_ESCAPE, 3},
                  {FishingOutcomeType::FISHING_OUTCOME_NO_CATCH, 100}};

  EXPECT_EQ(exp_outcomes, fc.calculate_fishing_outcomes(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FISHING, 100);
  creature->set_skills(skills);

  exp_outcomes = {{FishingOutcomeType::FISHING_OUTCOME_CATCH, 50},
                  {FishingOutcomeType::FISHING_OUTCOME_NIBBLE, 46},
                  {FishingOutcomeType::FISHING_OUTCOME_ESCAPE, 41},
                  {FishingOutcomeType::FISHING_OUTCOME_NO_CATCH, 100}};

  EXPECT_EQ(exp_outcomes, fc.calculate_fishing_outcomes(creature));
}

TEST(SW_Engine_Calculator_FishingCalculator, get_item_status_outcome_modifier)
{
  FishingCalculator fc;
  ItemPtr fishing_rod = std::make_shared<MiscItem>();

  EXPECT_EQ(0, fc.get_item_status_outcome_modifier(nullptr));

  std::map<ItemStatus, int> vals = { {ItemStatus::ITEM_STATUS_CURSED, -10}, {ItemStatus::ITEM_STATUS_UNCURSED, 0}, {ItemStatus::ITEM_STATUS_BLESSED, 10} };

  for (const auto& v : vals)
  {
    fishing_rod->set_status(v.first);
    EXPECT_EQ(v.second, fc.get_item_status_outcome_modifier(fishing_rod));
  }
}
