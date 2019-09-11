#include "gtest/gtest.h"

TEST(SW_Display_SDLCursorLocation, reset)
{
  SDLCursorLocation curs(3, 3);
  curs.incr();
  curs.incr();

  curs.reset();

  EXPECT_EQ(make_pair(0, 0), curs.get_yx());
}

TEST(SW_Display_SDLCursorLocation, max_values)
{
  SDLCursorLocation curs(5, 5);

  curs.set_y(2);
  curs.set_x(3);

  curs.set_y(6);
  curs.set_x(12);

  EXPECT_EQ(2, curs.get_y());
  EXPECT_EQ(3, curs.get_x());
}

TEST(SW_Display_SDLCursorLocation, init_and_set)
{
  SDLCursorLocation curs(5, 5);

  EXPECT_EQ(0, curs.get_y());
  EXPECT_EQ(0, curs.get_x());

  curs.set_y(4);
  curs.set_x(3);

  EXPECT_EQ(4, curs.get_y());
  EXPECT_EQ(3, curs.get_x());
}

TEST(SW_Display_SDLCursorLocation, incr)
{
  SDLCursorLocation curs(5, 5);

  int max_y = 5;
  int max_x = 10;

  int y = 0;
  int x = 0;

  while (y != max_y && x != max_x)
  {
    curs.incr();

    int new_y = curs.get_y();
    int new_x = curs.get_x();

    bool incr_ok = ((new_y == y && new_x == x + 1) || (new_y == y + 1 && new_x == 0));

    EXPECT_TRUE(incr_ok);

    y = new_y;
    x = new_x;
  }
}