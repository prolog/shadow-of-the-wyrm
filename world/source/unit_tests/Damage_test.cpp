#include "gtest/gtest.h"

TEST(SW_World_Damage, contains_dam_type)
{
  StatusAilments sa;
  Damage damage(5, 6, 7, DamageType::DAMAGE_TYPE_SHADOW, {}, false, false, false, false, false, true, 0, sa);
  
  EXPECT_TRUE(damage.contains(DamageType::DAMAGE_TYPE_SHADOW));
  EXPECT_FALSE(damage.contains(DamageType::DAMAGE_TYPE_HOLY));

  std::shared_ptr<Damage> addl_damage1(new Damage(1, 2, 3, DamageType::DAMAGE_TYPE_PIERCE, {}, false, false, false, false, false, false, 0, sa));
  std::shared_ptr<Damage> addl_damage2(new Damage(1, 2, 3, DamageType::DAMAGE_TYPE_HOLY, {}, false, false, false, false, false, false, 0, sa));
  std::shared_ptr<Damage> addl_damage3(new Damage(1, 2, 3, DamageType::DAMAGE_TYPE_ACID, {}, false, false, false, false, false, false, 0, sa));

  addl_damage1->set_additional_damage(addl_damage2);
  addl_damage2->set_additional_damage(addl_damage3);
  damage.set_additional_damage(addl_damage1);

  EXPECT_TRUE(damage.contains(DamageType::DAMAGE_TYPE_SHADOW));
  EXPECT_TRUE(damage.contains(DamageType::DAMAGE_TYPE_PIERCE));
  EXPECT_TRUE(damage.contains(DamageType::DAMAGE_TYPE_HOLY));
  EXPECT_TRUE(damage.contains(DamageType::DAMAGE_TYPE_ACID));

  EXPECT_FALSE(damage.contains(DamageType::DAMAGE_TYPE_HEAT));
}

TEST(SW_World_Damage, serialization_id)
{
  Damage damage;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_DAMAGE, damage.get_class_identifier());
}

TEST(SW_World_Damage, saveload)
{
  StatusAilments sa;
  Damage damage(5, 6, 7, DamageType::DAMAGE_TYPE_SHADOW, {}, false, false, false, false, false, true, 0, sa);
  std::shared_ptr<Damage> addl_damage(new Damage(6, 7, 8, DamageType::DAMAGE_TYPE_PIERCE, {}, false, false, false, false, false, true, 0, sa));
  damage.set_additional_damage(addl_damage);
  damage.set_chaotic(true);
  damage.set_effect_bonus(42);
  damage.set_piercing(true);
  damage.set_vorpal(true);
  damage.set_draining(true);

  vector<string> slay_races;
  slay_races.push_back("elf");
  slay_races.push_back("dwarf");

  damage.set_slays_races(slay_races);

  Damage damage2;

  ostringstream ss;

  damage.serialize(ss);

  istringstream iss(ss.str());

  damage2.deserialize(iss);

  bool damage_ok = (damage == damage2);
  bool chaotic_flag_ok = (damage2.get_chaotic());
  bool vorp_flag_ok = (damage2.get_vorpal());
  bool drain_flag_ok = (damage2.get_draining());
  bool incorp_flag_ok = damage2.get_incorporeal();
  bool slays_ok = find(slay_races.begin(), slay_races.end(), "elf") != slay_races.end();

  EXPECT_TRUE(damage_ok);
  EXPECT_TRUE(chaotic_flag_ok);
  EXPECT_TRUE(vorp_flag_ok);
  EXPECT_TRUE(drain_flag_ok);
  EXPECT_TRUE(incorp_flag_ok);
  EXPECT_TRUE(slays_ok);
}
