#include "gtest/gtest.h"
#include "Weapon.hpp"

TEST(SW_Engine_Calculators_MeleeWeaponRangeCalculator, unarmed_range)
{
  CreaturePtr creature = std::make_shared<Creature>();
  MeleeWeaponRangeCalculator mwrc;

  EXPECT_EQ(0, mwrc.get_primary_melee_range(nullptr));
  EXPECT_EQ(1, mwrc.get_primary_melee_range(creature));

  creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_PRIMARY_MELEE_RANGE, std::to_string(4));

  EXPECT_EQ(4, mwrc.get_primary_melee_range(creature));
}

TEST(SW_Engine_Calculators_MeleeWeaponRangeCalculator, armed_range)
{
  CreaturePtr creature = std::make_shared<Creature>();
  MeleeWeaponRangeCalculator mwrc;
  WeaponPtr melee_weapon = std::make_shared<MeleeWeapon>();
  creature->get_equipment().set_item(melee_weapon, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  EXPECT_EQ(1, mwrc.get_primary_melee_range(creature));

  melee_weapon->set_range(3);

  EXPECT_EQ(3, mwrc.get_primary_melee_range(creature));
}
