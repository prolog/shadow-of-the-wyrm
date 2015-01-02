#include "gtest/gtest.h"
#include "RNG.hpp"

TEST(SL_Display_CursesDisplay, serialization_id)
{
  CursesDisplay cd;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CURSES_DISPLAY, cd.get_class_identifier());
}

class SL_Display_CursesDisplayFixture : public ::testing::Test
{
  protected:
    void SetUp();

    CursesDisplay curses_display;
};

void SL_Display_CursesDisplayFixture::SetUp()
{
  curses_display.TERMINAL_MAX_ROWS = RNG::range(0, 25);
  curses_display.TERMINAL_MAX_COLS = RNG::range(0, 80);
  curses_display.FIELD_SPACE = RNG::range(0, 2);

  // I should probably mock up WINDOW*, but I don't really care to right now...

  curses_display.MSG_BUFFER_LAST_Y = RNG::range(0, 1);
  curses_display.MSG_BUFFER_LAST_X = RNG::range(0, 80);
  curses_display.can_use_colour = RNG::percent_chance(50);
}

TEST_F(SL_Display_CursesDisplayFixture, saveload)
{
  CursesDisplay cd = curses_display;

  ostringstream ss;

  cd.serialize(ss);

  istringstream iss(ss.str());

  CursesDisplay cd2;

  cd2.deserialize(iss);

  EXPECT_TRUE(cd == cd2);
}
