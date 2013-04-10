#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Magic_MagicCommandFactory, serialization_id)
{
  MagicCommandFactory mcf;

  EXPECT_EQ(CLASS_ID_MAGIC_COMMAND_FACTORY, mcf.get_class_identifier());
}

