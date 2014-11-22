#include "gtest/gtest.h"

class TanningCalculatorTestFixture : public ::testing::Test
{
  public:
    vector<int> calculate_evade_probabilities(CreaturePtr creature);
    vector<int> calculate_soak_probabilities(CreaturePtr creature);
};

vector<int> TanningCalculatorTestFixture::calculate_evade_probabilities(CreaturePtr creature)
{
  TanningCalculator tc;

  return tc.calculate_evade_probabilities(creature);
}

vector<int> TanningCalculatorTestFixture::calculate_soak_probabilities(CreaturePtr creature)
{
  TanningCalculator tc;

  return tc.calculate_soak_probabilities(creature);
}

TEST_F(TanningCalculatorTestFixture, calculate_evade_probabilities)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  vector<int> ev_p = calculate_evade_probabilities(creature);

  EXPECT_EQ(vector<int>({ 10, 10, 10, 10, 10 }), ev_p);

  skills.set_value(SKILL_GENERAL_TANNING, 105);
  creature->set_skills(skills);

  ev_p = calculate_evade_probabilities(creature);

  EXPECT_EQ(vector<int>({100, 95, 90, 85, 80}), ev_p);

  skills.set_value(SKILL_GENERAL_TANNING, 25);
  creature->set_skills(skills);

  ev_p = calculate_evade_probabilities(creature);

  EXPECT_EQ(vector<int>({ 25, 20, 15, 10, 10 }), ev_p);
}

TEST_F(TanningCalculatorTestFixture, calculate_soak_probabilities)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  vector<int> sk_p = calculate_soak_probabilities(creature);

  EXPECT_EQ(vector<int>({ 10, 10, 10, 10, 10 }), sk_p);

  skills.set_value(SKILL_GENERAL_TANNING, 105);
  creature->set_skills(skills);

  sk_p = calculate_soak_probabilities(creature);

  EXPECT_EQ(vector<int>({ 100, 95, 90, 85, 80 }), sk_p);

  skills.set_value(SKILL_GENERAL_TANNING, 24);
  creature->set_skills(skills);

  sk_p = calculate_soak_probabilities(creature);

  EXPECT_EQ(vector<int>({ 24, 19, 14, 10, 10 }), sk_p);
}

