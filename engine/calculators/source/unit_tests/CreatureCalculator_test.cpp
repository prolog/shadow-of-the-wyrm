#include "gtest/gtest.h"
#include "MobileDecisionStrategy.hpp"

TEST(SW_Engine_Calculators_CreatureCalculator, get_combat_assist_pct)
{
  CreatureCalculator cc;

  EXPECT_EQ(0, cc.get_combat_assist_pct(nullptr));

  CreaturePtr c = std::make_shared<Creature>();

  EXPECT_EQ(20, cc.get_combat_assist_pct(c));

  DecisionStrategyPtr d = std::make_unique<MobileDecisionStrategy>(nullptr);
  d->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SENTRY, std::to_string(true));
  c->set_decision_strategy(std::move(d));

  EXPECT_EQ(100, cc.get_combat_assist_pct(c));
}