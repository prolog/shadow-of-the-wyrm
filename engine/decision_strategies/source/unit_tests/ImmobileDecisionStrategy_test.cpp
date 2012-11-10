#include "gtest/gtest.h"
#include "ControllerFactory.hpp"

TEST(SL_Engine_DecisionStrategy_ImmobileDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(CLASS_ID_NULL_KEYBOARD_CONTROLLER);

  ImmobileDecisionStrategy ids(null_controller);

  EXPECT_EQ(CLASS_ID_IMMOBILE_DECISION_STRATEGY, ids.get_class_identifier());
}

