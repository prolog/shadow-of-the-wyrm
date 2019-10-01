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

TEST(SW_Display_SDLCursorLocation, crossing_lines)
{
  SDLCursorLocation curs(25, 80);
  curs.set_y(0);
  curs.set_x(79);

  curs.incr();

  EXPECT_EQ(1, curs.get_y());
  EXPECT_EQ(0, curs.get_x());

  curs.decr();

  EXPECT_EQ(0, curs.get_y());
  EXPECT_EQ(79, curs.get_x());
}

TEST(SW_Display_SDLCursorLocation, incr)
{
  SDLCursorLocation curs(5, 5);

  int max_y = 5;
  int max_x = 5;

  int y = 0;
  int x = 0;

  while (y != max_y - 1 && x != max_x - 1)
  {
    bool incr = curs.incr();

    int new_y = curs.get_y();
    int new_x = curs.get_x();

    bool incr_ok = ((new_y == y && new_x == x + 1) || (new_y == y + 1 && new_x == 0));

    EXPECT_TRUE(incr && incr_ok);

    y = new_y;
    x = new_x;
  }
}

TEST(SW_Display_SDLCursorLocation, decr)
{
  SDLCursorLocation curs(5, 5);

  int max_y = 5;
  int max_x = 5;

  int y = 4;
  int x = 4;

  curs.set_y(y);
  curs.set_x(x);

  while (y > 0 && x > 0)
  {
    bool decr = curs.decr();

    int new_y = curs.get_y();
    int new_x = curs.get_x();

    bool decr_ok = ((new_y == y && new_x == x - 1) || (new_y == y - 1 && new_x == max_x - 1));

    EXPECT_TRUE(decr && decr_ok);

    y = new_y;
    x = new_x;
  }
}