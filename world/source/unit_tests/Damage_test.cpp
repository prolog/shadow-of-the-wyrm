#include "gtest/gtest.h"

TEST(SL_World_Damage, serialization_id)
{
  Damage damage;

  EXPECT_EQ(CLASS_ID_DAMAGE, damage.get_class_identifier());
}

TEST(SL_World_Damage, saveload)
{
  Damage damage(5,6,7,DAMAGE_TYPE_SHADOW, false);
  std::shared_ptr<Damage> addl_damage(new Damage(6,7,8,DAMAGE_TYPE_PIERCE, false));
  damage.set_additional_damage(addl_damage);
  damage.set_chaotic(true);

  Damage damage2;

  ostringstream ss;

  damage.serialize(ss);

  istringstream iss(ss.str());

  damage2.deserialize(iss);

  bool damage_ok = (damage == damage2);
  bool chaotic_flag_ok = (damage2.get_chaotic());

  EXPECT_TRUE(damage_ok);
  EXPECT_TRUE(chaotic_flag_ok);
}
