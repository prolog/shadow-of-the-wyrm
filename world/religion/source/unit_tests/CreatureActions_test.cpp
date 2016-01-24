#include "gtest/gtest.h"

TEST(SW_World_Religion_CreatureActions, serialization_id)
{
  CreatureActions ca;
  
  EXPECT_EQ(ClassIdentifier::CLASS_ID_CREATURE_ACTIONS, ca.get_class_identifier());
}

TEST(SW_World_Religion_CreatureActions, saveload)
{
  CreatureActions ca, ca2;

  ca.set_action_value("fun", true);
  ca.set_action_value("pizza", false);
  ca.set_action_value("COWBOYS MONKEYS NINJAS", true);

  ostringstream ss;

  ca.serialize(ss);

  istringstream iss(ss.str());

  ca2.deserialize(iss);

  EXPECT_TRUE(ca == ca2);
}

