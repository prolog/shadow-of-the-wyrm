#include "gtest/gtest.h"

TEST(SW_World_Armour, get_is_good_cstat)
{
  Armour a;

  EXPECT_FALSE(a.get_is_good());

  a.set_evade(2);

  EXPECT_FALSE(a.get_is_good());

  a.set_evade(6);

  EXPECT_TRUE(a.get_is_good());

  a.set_soak(-4);

  EXPECT_FALSE(a.get_is_good());

  a.set_addl_damage(10);

  EXPECT_TRUE(a.get_is_good());
}


TEST(SW_World_Armour, serialization_id)
{
  Armour armour;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ARMOUR, armour.get_class_identifier());
}

TEST(SW_World_Armour, saveload)
{
  Armour armour, armour2;

  armour.set_evade(3);

  ostringstream ss;

  armour.serialize(ss);

  istringstream iss(ss.str());

  armour2.deserialize(iss);

  EXPECT_TRUE(armour == armour2);
}
