#include "gtest/gtest.h"
#include "ControllerFactory.hpp"

TEST(SW_Engine_DecisionStrategy_ImmobileDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);

  ImmobileDecisionStrategy ids(null_controller);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_IMMOBILE_DECISION_STRATEGY, ids.get_class_identifier());
}

