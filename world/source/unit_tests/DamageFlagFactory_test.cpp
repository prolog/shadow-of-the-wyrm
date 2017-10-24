#include "gtest/gtest.h"

TEST(SW_World_DamageFlagFactory, damage_flag_values)
{
  DamageFlagFactory dff;

  EXPECT_EQ(TextKeys::DAMAGE_CHAOTIC, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_CHAOTIC).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_VORPAL, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_VORPAL).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_DRAINING, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_DRAINING).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_ETHEREAL, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_ETHEREAL).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_PIERCING, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_PIERCING).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_INCORPOREAL, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_INCORPOREAL).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_SCYTHING, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_SCYTHING).get_description_sid());
  EXPECT_EQ(TextKeys::DAMAGE_EXPLOSIVE, dff.create_damage_flag(DamageFlagType::DAMAGE_FLAG_EXPLOSIVE).get_description_sid());
}
