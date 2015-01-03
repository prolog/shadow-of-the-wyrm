#include "gtest/gtest.h"

TEST(SL_World_Ammunition, serialization_id)
{
  Ammunition ammo;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AMMUNITION, ammo.get_class_identifier());
}

TEST(SL_World_Ammunition, saveload)
{
  Ammunition ammo, ammo2;

  ostringstream ss;

  ammo.set_description_sid("test");

  ammo.serialize(ss);

  istringstream iss(ss.str());

  ammo2.deserialize(iss);

  EXPECT_TRUE(ammo == ammo2);
}
