#include "gtest/gtest.h"

TEST(SL_World_Ammunition, serialization_id)
{
  Ammunition ammo;

  EXPECT_EQ(CLASS_ID_AMMUNITION, ammo.get_class_identifier());
}

TEST(SL_World_Ammunition, saveload)
{
  Ammunition ammo, ammo2;

  ostringstream ss;

  ammo.serialize(ss);

  istringstream iss(ss.str());

  ammo2.deserialize(iss);

  EXPECT_TRUE(ammo == ammo2);
}
