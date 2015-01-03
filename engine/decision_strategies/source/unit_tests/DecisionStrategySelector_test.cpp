#include "gtest/gtest.h"

// This function is unsafe for anything using the creature's controller!
TEST(SL_Engine_DecisionStrategies_DecisionStrategySelector, select_decision_strategy)
{
  CreaturePtr c = std::make_shared<Creature>();

  ControllerPtr nullc;

  AutomaticMovement& am = c->get_automatic_movement_ref();
  am.set_engaged(false);
  am.set_direction(DIRECTION_NORTH);

  DecisionStrategyPtr dec = std::make_shared<AutomaticMovementDecisionStrategy>(am, nullc);
  c->set_decision_strategy(dec);

  c->set_is_player(true, nullc);

  // Setting the creature to be a player resets to a non-automatic-
  // movement decision strategy, the PlayerDecisionStrategy.
  dec = DecisionStrategySelector::select_decision_strategy(c);
  EXPECT_EQ(ClassIdentifier::CLASS_ID_PLAYER_DECISION_STRATEGY, dec->get_class_identifier());

  am.set_engaged(true);

  // Setting automatic movement correctly should return an instance of an
  // AutomaticMovementDecisionStrategy.
  dec = DecisionStrategySelector::select_decision_strategy(c);
  EXPECT_EQ(ClassIdentifier::CLASS_ID_AUTOMATIC_MOVEMENT_DECISION_STRATEGY, dec->get_class_identifier());
}

