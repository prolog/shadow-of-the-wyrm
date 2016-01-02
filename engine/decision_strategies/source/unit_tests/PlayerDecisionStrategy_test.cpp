#include "gtest/gtest.h"
#include "ControllerFactory.hpp"

TEST(SL_Engine_DecisionStrategy_PlayerDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);
  
  PlayerDecisionStrategy pds(null_controller);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PLAYER_DECISION_STRATEGY, pds.get_class_identifier());
}

TEST(SL_Engine_DecisionStrategy_PlayerDecisionStrategy, saveload_to_test_decision_strategy_properties)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);

  PlayerDecisionStrategy pds(null_controller);
  pds.set_property("k1", "v1");
  pds.set_property("test", "foo");

  PlayerDecisionStrategy pds2(null_controller);

  ostringstream ss;

  pds.serialize(ss);

  istringstream iss(ss.str());

  pds2.deserialize(iss);

  EXPECT_TRUE(pds == pds2);

  EXPECT_EQ("v1", pds2.get_property("k1"));
  EXPECT_EQ("foo", pds2.get_property("test"));
}