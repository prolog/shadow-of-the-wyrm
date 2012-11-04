#include "gtest/gtest.h"

TEST(SL_Display_CursesDisplay, serialization_id)
{
  CursesDisplay cd;

  EXPECT_EQ(CLASS_ID_CURSES_DISPLAY, cd.get_class_identifier());
}

