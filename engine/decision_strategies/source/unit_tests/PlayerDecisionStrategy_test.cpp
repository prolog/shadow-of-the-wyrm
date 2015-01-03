#include "gtest/gtest.h"
#include "ControllerFactory.hpp"

TEST(SL_Engine_DecisionStrategy_PlayerDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(CLASS_ID_NULL_KEYBOARD_CONTROLLER);
  
  PlayerDecisionStrategy pds(null_controller);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PLAYER_DECISION_STRATEGY, pds.get_class_identifier());
}

