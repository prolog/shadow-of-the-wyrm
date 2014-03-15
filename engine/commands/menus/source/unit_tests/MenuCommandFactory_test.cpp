#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Menus_MenuCommandFactory, serialization_id)
{
  MenuCommandFactory mcf;

  EXPECT_EQ(CLASS_ID_MENU_COMMAND_FACTORY, mcf.get_class_identifier());
}

