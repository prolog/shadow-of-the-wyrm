#include "gtest/gtest.h"
#include "ControllerFactory.hpp"

TEST(SW_Engine_DecisionStrategy_PlayerDecisionStrategy, serialization_id)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);
  
  PlayerDecisionStrategy pds(null_controller);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_PLAYER_DECISION_STRATEGY, pds.get_class_identifier());
}

TEST(SW_Engine_DecisionStrategy_PlayerDecisionStrategy, saveload_autopickup_settings)
{
  ControllerPtr null_controller = ControllerFactory::create_controller(ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER);

  PlayerDecisionStrategy pds(null_controller);
  pds.set_autopickup(true);

  set<ItemType> ap_types = { ItemType::ITEM_TYPE_AMULET, ItemType::ITEM_TYPE_CURRENCY };
  pds.set_autopickup_types(ap_types);

  PlayerDecisionStrategy pds2(null_controller);

  EXPECT_FALSE(pds2.get_autopickup());
  EXPECT_EQ(0, pds2.get_autopickup_types().size());

  ostringstream ss;
  pds.serialize(ss);
  istringstream iss(ss.str());
  pds2.deserialize(iss);

  EXPECT_TRUE(pds2.get_autopickup());
  EXPECT_EQ(ap_types, pds2.get_autopickup_types());
}

TEST(SW_Engine_DecisionStrategy_PlayerDecisionStrategy, saveload_to_test_decision_strategy_properties)
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