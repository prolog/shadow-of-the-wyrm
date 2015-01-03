#include "gtest/gtest.h"

TEST(SL_World_Damage, contains_dam_type)
{
  StatusAilments sa;
  Damage damage(5, 6, 7, DAMAGE_TYPE_SHADOW, false, false, 0, sa);
  
  EXPECT_TRUE(damage.contains(DAMAGE_TYPE_SHADOW));
  EXPECT_FALSE(damage.contains(DAMAGE_TYPE_HOLY));

  std::shared_ptr<Damage> addl_damage1(new Damage(1, 2, 3, DAMAGE_TYPE_PIERCE, false, false, 0, sa));
  std::shared_ptr<Damage> addl_damage2(new Damage(1, 2, 3, DAMAGE_TYPE_HOLY, false, false, 0, sa));
  std::shared_ptr<Damage> addl_damage3(new Damage(1, 2, 3, DAMAGE_TYPE_ACID, false, false, 0, sa));

  addl_damage1->set_additional_damage(addl_damage2);
  addl_damage2->set_additional_damage(addl_damage3);
  damage.set_additional_damage(addl_damage1);

  EXPECT_TRUE(damage.contains(DAMAGE_TYPE_SHADOW));
  EXPECT_TRUE(damage.contains(DAMAGE_TYPE_PIERCE));
  EXPECT_TRUE(damage.contains(DAMAGE_TYPE_HOLY));
  EXPECT_TRUE(damage.contains(DAMAGE_TYPE_ACID));

  EXPECT_FALSE(damage.contains(DAMAGE_TYPE_HEAT));
}

TEST(SL_World_Damage, serialization_id)
{
  Damage damage;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DAMAGE, damage.get_class_identifier());
}

TEST(SL_World_Damage, saveload)
{
  StatusAilments sa;
  Damage damage(5,6,7,DAMAGE_TYPE_SHADOW, false, false, 0, sa);
  std::shared_ptr<Damage> addl_damage(new Damage(6,7,8,DAMAGE_TYPE_PIERCE, false, false, 0, sa));
  damage.set_additional_damage(addl_damage);
  damage.set_chaotic(true);
  damage.set_effect_bonus(42);
  damage.set_piercing(true);

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
