#include "gtest/gtest.h"

TEST(SW_Engine_Commands_CommandFactory, serialization_id)
{
  CommandFactory cf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_COMMAND_FACTORY, cf.get_class_identifier());
}

