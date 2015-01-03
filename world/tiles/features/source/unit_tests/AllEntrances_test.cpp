#include "gtest/gtest.h"
#include "Door.hpp"
#include "Gate.hpp"

TEST(SL_World_Tiles_Feature_Entrances, saveload)
{
  Door door, door2;
  LockPtr lock = LockPtr(new Lock());
  Gate gate, gate2;

  lock->set_lock_id("fdsafdsa");

  ostringstream ss, ss2;

  door.get_state_ref().set_state(ENTRANCE_TYPE_OPEN);
  door.set_maximum_size(CREATURE_SIZE_SMALL);
  door.set_lock(lock);

  gate.get_state_ref().set_state(ENTRANCE_TYPE_CLOSED);
  gate.set_maximum_size(CREATURE_SIZE_LARGE);

  door.serialize(ss);
  gate.serialize(ss2);

  istringstream iss(ss.str()), iss2(ss2.str());

  door2.deserialize(iss);
  gate2.deserialize(iss2);

  EXPECT_TRUE(door == door2);
  EXPECT_TRUE(gate == gate2);
}

TEST(SL_World_Tiles_Feature_Entrances, serialization_id)
{
  Door door;
  Gate gate;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DOOR, door.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_GATE, gate.get_class_identifier());
}

