#include "gtest/gtest.h"
#include "ControllerFactory.hpp"
#include "CoordUtils.hpp"

TEST(SW_Engine_DecisionStrategy_MobileDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);
  
  MobileDecisionStrategy mds(null_controller);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MOBILE_DECISION_STRATEGY, mds.get_class_identifier());
}

TEST(SW_Engine_DecisionStrategy_MobileDecisionStrategy, automove_coords)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);
  
  MobileDecisionStrategy mds(null_controller);

  Coordinate c = mds.get_automove_coords();

  EXPECT_EQ(c, CoordUtils::end());

  c = make_pair(3, 4);

  mds.set_automove_coords(c);

  EXPECT_EQ(c, mds.get_automove_coords());
}

