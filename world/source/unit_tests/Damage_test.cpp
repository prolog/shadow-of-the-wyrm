#include "gtest/gtest.h"

TEST(SL_World_Damage, serialization_id)
{
  Damage damage;

  EXPECT_EQ(CLASS_ID_DAMAGE, damage.get_class_identifier());
}

TEST(SL_World_Damage, saveload)
{
  Damage damage(5,6,7,DAMAGE_TYPE_SHADOW);
  boost::shared_ptr<Damage> addl_damage(new Damage(6,7,8,DAMAGE_TYPE_PIERCE));
  damage.set_additional_damage(addl_damage);

  Damage damage2;

  ostringstream ss;

  damage.serialize(ss);

  istringstream iss(ss.str());

  damage2.deserialize(iss);

  EXPECT_TRUE(damage == damage2);
}
