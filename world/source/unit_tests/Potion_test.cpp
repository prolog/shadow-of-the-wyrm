#include "gtest/gtest.h"

TEST(SL_World_Potion, serialization_id)
{
  Potion potion;

  EXPECT_EQ(CLASS_ID_POTION, potion.get_class_identifier());
}

TEST(SL_World_Potion, saveload)
{
  Potion potion, potion2;

  potion.set_quantity(10);
  potion.set_has_damage(true);

  Damage d(1, 4, 1, DAMAGE_TYPE_HEAT);
  potion.set_damage(d);

  ostringstream ss;

  potion.serialize(ss);

  istringstream iss(ss.str());

  potion2.deserialize(iss);

  EXPECT_TRUE(potion == potion2);
}
