#include "gtest/gtest.h"

TEST(SW_World_Potion, serialization_id)
{
  Potion potion;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_POTION, potion.get_class_identifier());
}

TEST(SW_World_Potion, saveload)
{
  Potion potion, potion2;

  potion.set_quantity(10);
  potion.set_has_damage(true);
  potion.set_poisoned(true);

  Damage d(1, 4, 1, DamageType::DAMAGE_TYPE_HEAT, {}, false, false, false, false, 0, {});
  potion.set_damage(d);

  ostringstream ss;

  potion.serialize(ss);

  istringstream iss(ss.str());

  potion2.deserialize(iss);

  EXPECT_TRUE(potion == potion2);
}
