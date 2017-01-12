#include "gtest/gtest.h"

TEST(SW_World_DamageFlag, damage_flag)
{
  DamageFlag df(DamageFlagType::DAMAGE_FLAG_CHAOTIC, "some_sid");

  EXPECT_EQ(DamageFlagType::DAMAGE_FLAG_CHAOTIC, df.get_flag());
  EXPECT_EQ("some_sid", df.get_description_sid());

  DamageFlag df2(DamageFlagType::DAMAGE_FLAG_INCORPOREAL, "sid2");

  EXPECT_EQ(DamageFlagType::DAMAGE_FLAG_INCORPOREAL, df2.get_flag());
  EXPECT_EQ("sid2", df2.get_description_sid());
}

