#include "gtest/gtest.h"
#include "Door.hpp"
#include "Gate.hpp"

TEST(SL_World_Tiles_Feature_Entrances, serialization_id)
{
  Door door;
  Gate gate;

  EXPECT_EQ(CLASS_ID_DOOR, door.get_class_identifier());
  EXPECT_EQ(CLASS_ID_GATE, gate.get_class_identifier());
}

