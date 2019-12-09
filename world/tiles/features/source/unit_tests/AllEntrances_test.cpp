#include "gtest/gtest.h"
#include "Door.hpp"
#include "Gate.hpp"

TEST(SW_World_Tiles_Feature_Entrances, saveload)
{
  Symbol s('+', Colour::COLOUR_WHITE);
  Door door(s);
  Door door2(s);
  LockPtr lock = LockPtr(new Lock());
  Gate gate(s);
  Gate gate2(s);

  lock->set_lock_id("fdsafdsa");

  ostringstream ss, ss2;

  door.get_state_ref().set_state(EntranceStateType::ENTRANCE_TYPE_OPEN);
  door.set_maximum_size(CreatureSize::CREATURE_SIZE_SMALL);
  door.set_lock(lock);

  gate.get_state_ref().set_state(EntranceStateType::ENTRANCE_TYPE_CLOSED);
  gate.set_maximum_size(CreatureSize::CREATURE_SIZE_LARGE);

  door.serialize(ss);
  gate.serialize(ss2);

  istringstream iss(ss.str()), iss2(ss2.str());

  door2.deserialize(iss);
  gate2.deserialize(iss2);

  EXPECT_TRUE(door == door2);
  EXPECT_TRUE(gate == gate2);
}

TEST(SW_World_Tiles_Feature_Entrances, serialization_id)
{
  Symbol s('+', Colour::COLOUR_WHITE);

  Door door(s);
  Gate gate(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DOOR, door.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_GATE, gate.get_class_identifier());
}

