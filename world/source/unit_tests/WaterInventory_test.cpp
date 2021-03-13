#include "gtest/gtest.h"

TEST(SW_World_WaterInventory, serialization_id)
{
  WaterInventory wi;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_WATER_INVENTORY, wi.get_class_identifier());
}
