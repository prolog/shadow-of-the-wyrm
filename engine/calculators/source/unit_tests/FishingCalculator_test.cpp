#include "gtest/gtest.h"

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
