#include "gtest/gtest.h"

TEST(SW_World_Race, operator_less_than)
{
  Race first;
  Race second;

  first.set_race_id("aaa");
  second.set_race_id("aab");

  EXPECT_TRUE( first < second );

  first.set_race_id("3");
  second.set_race_id("2");

  EXPECT_FALSE( first < second );
}
