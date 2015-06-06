#include "gtest/gtest.h"

TEST(SL_World_CreatureGenerationOptions, parse_options)
{
  string parse_1 = "fdsa";
  CreatureGenerationOptions cgo_1;
  cgo_1.parse(parse_1);

  EXPECT_EQ("fdsa", cgo_1.get_id());

  string parse_2 = "id=cherif;hostility=player:true;someothervalue";
  CreatureGenerationOptions cgo_2;
  cgo_2.parse(parse_2);

  EXPECT_EQ("someothervalue", cgo_2.get_id());
  EXPECT_TRUE(cgo_2.get_hostility("player"));

  string parse_3 = "id = jcd; hostility= player : true; someothervalue";
  CreatureGenerationOptions cgo_3;
  cgo_3.parse(parse_3);

  EXPECT_EQ("someothervalue", cgo_3.get_id());
  EXPECT_TRUE(cgo_3.get_hostility("player"));
}
