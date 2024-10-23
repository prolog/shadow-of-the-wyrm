#include "gtest/gtest.h"
#include <vector>
TEST(SW_Engine_Actions_TileMovementConfirmationDetails, init)
{
  TileMovementConfirmationDetails tmcd;

  EXPECT_FALSE(tmcd.get_require_prompt());
  EXPECT_EQ("", tmcd.get_confirmation_message());
  EXPECT_EQ("", tmcd.get_sound_effect_id());
  EXPECT_EQ("", tmcd.get_post_movement_message_sid());

  bool req = true;
  std::vector<std::string> v = {"a", "b", "c"};
  TileMovementConfirmationDetails tmcd2(req, v[0], v[1], v[2]);
  EXPECT_EQ(req, tmcd2.get_require_prompt());
  EXPECT_EQ(v[0], tmcd2.get_confirmation_message());
  EXPECT_EQ(v[1], tmcd2.get_sound_effect_id());
  EXPECT_EQ(v[2], tmcd2.get_post_movement_message_sid());
}

