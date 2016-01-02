#include "gtest/gtest.h"

TEST(SL_World_Weapon, serialization_ids)
{
  MeleeWeapon melee;
  RangedWeapon ranged;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MELEE_WEAPON, melee.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_RANGED_WEAPON, ranged.get_class_identifier());
}

TEST(SL_World_Weapon, saveload)
{
  MeleeWeapon m, m2;
  RangedWeapon r, r2;

  ostringstream ss, ss2;

  m.set_quantity(3);
  m.set_to_hit(17);
  m.set_addl_damage(4);
  m.set_speed_bonus(2);
  m.set_additional_property("testprop", "testval");
  r.set_quantity(1333);
  r.set_value(444);
  r.set_glowing(true);

  vector<string> slay_races;
  slay_races.push_back("elf");
  slay_races.push_back("dwarf");

  m.set_slays_races(slay_races);
  r.set_slays_races(slay_races);

  m.serialize(ss);
  r.serialize(ss2);

  istringstream iss(ss.str());
  istringstream iss2(ss2.str());

  m2.deserialize(iss);
  r2.deserialize(iss2);

  slay_races = m2.get_slays_races();
  EXPECT_TRUE(find(slay_races.begin(), slay_races.end(), "elf") != slay_races.end());
  EXPECT_EQ(17, m2.get_to_hit());
  EXPECT_EQ(4, m2.get_addl_damage());
  EXPECT_EQ(2, m2.get_speed_bonus());
  EXPECT_EQ(444, r2.get_value());
}
