#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Screens_ScreenCommandFactory, serialization_id)
{
  ScreenCommandFactory scf;

  EXPECT_EQ(CLASS_ID_SCREEN_COMMAND_FACTORY, scf.get_class_identifier());
}

