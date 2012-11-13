#include "gtest/gtest.h"

TEST(SL_World_Armour, serialization_id)
{
  Armour armour;

  EXPECT_EQ(CLASS_ID_ARMOUR, armour.get_class_identifier());
}

TEST(SL_World_Armour, saveload)
{
  Armour armour, armour2;

  armour.set_evade(3);

  ostringstream ss;

  armour.serialize(ss);

  istringstream iss(ss.str());

  armour2.deserialize(iss);

  EXPECT_TRUE(armour == armour2);
}
