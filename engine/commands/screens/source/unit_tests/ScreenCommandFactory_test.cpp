#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Screens_ScreenCommandFactory, serialization_id)
{
  ScreenCommandFactory scf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SCREEN_COMMAND_FACTORY, scf.get_class_identifier());
}

