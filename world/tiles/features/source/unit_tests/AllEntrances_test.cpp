#include "gtest/gtest.h"
#include "Door.hpp"
#include "Gate.hpp"

TEST(SL_World_Tiles_Feature_Entrances, saveload)
{
  Door door, door2;
  Gate gate, gate2;

  ostringstream ss, ss2;

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

  EXPECT_EQ(CLASS_ID_DOOR, door.get_class_identifier());
  EXPECT_EQ(CLASS_ID_GATE, gate.get_class_identifier());
}

