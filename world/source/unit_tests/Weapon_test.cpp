#include "gtest/gtest.h"

TEST(SW_World_Weapon, get_is_good_resists)
{
  MeleeWeapon weapon;

  EXPECT_FALSE(weapon.get_is_good());

  Resistances r;
  r.set_resistance_value(DamageType::DAMAGE_TYPE_POISON, 0.08);
  weapon.set_resistances(r);

  EXPECT_FALSE(weapon.get_is_good());

  r.set_all_resistances_to(0.02);
  weapon.set_resistances(r);

  EXPECT_TRUE(weapon.get_is_good());
}

TEST(SW_World_Weapon, serialization_ids)
{
  MeleeWeapon melee;
  RangedWeapon ranged;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MELEE_WEAPON, melee.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_RANGED_WEAPON, ranged.get_class_identifier());
}

TEST(SW_World_Weapon, saveload)
{
  MeleeWeapon m, m2;
  RangedWeapon r, r2;

  ostringstream ss, ss2;

  m.set_quantity(3);
  m.set_to_hit(17);
  m.set_addl_damage(4);
  m.set_speed_bonus(2);
  m.set_hands_required(2);
  m.set_additional_property("testprop", "testval");
  m.set_range(6);
  r.set_quantity(1333);
  r.set_value(444);
  r.set_glowing(true);

  m.serialize(ss);
  r.serialize(ss2);

  istringstream iss(ss.str());
  istringstream iss2(ss2.str());

  m2.deserialize(iss);
  r2.deserialize(iss2);

  EXPECT_EQ(17, m2.get_to_hit());
  EXPECT_EQ(4, m2.get_addl_damage());
  EXPECT_EQ(2, m2.get_speed_bonus());
  EXPECT_EQ(2, m2.get_hands_required());
  EXPECT_EQ(6, m2.get_range());
  EXPECT_EQ(static_cast<size_t>(444), r2.get_value());
}
