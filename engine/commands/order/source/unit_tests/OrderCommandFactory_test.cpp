#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Help_OrderCommandFactory, serialization_id)
{
  OrderCommandFactory ocf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ORDER_COMMAND_FACTORY, ocf.get_class_identifier());
}

