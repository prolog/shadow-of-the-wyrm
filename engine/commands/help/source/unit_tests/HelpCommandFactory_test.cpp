#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Help_HelpCommandFactory, serialization_id)
{
  HelpCommandFactory hcf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_HELP_COMMAND_FACTORY, hcf.get_class_identifier());
}

