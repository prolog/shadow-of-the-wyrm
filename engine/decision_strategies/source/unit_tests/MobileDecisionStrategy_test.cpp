#include "gtest/gtest.h"
#include "ControllerFactory.hpp"

TEST(SL_Engine_DecisionStrategy_MobileDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(CLASS_ID_NULL_KEYBOARD_CONTROLLER);
  
  MobileDecisionStrategy mds(null_controller);

  EXPECT_EQ(CLASS_ID_MOBILE_DECISION_STRATEGY, mds.get_class_identifier());
}
