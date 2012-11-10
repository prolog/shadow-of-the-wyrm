#include "gtest/gtest.h"

TEST(SL_World_Inventory, serialization_id)
{
  Inventory inv;

  EXPECT_EQ(CLASS_ID_INVENTORY, inv.get_class_identifier());
}
