#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Inventory_InventoryCommandFactory, serialization_id)
{
  InventoryCommandFactory icf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_INVENTORY_COMMAND_FACTORY, icf.get_class_identifier());
}

