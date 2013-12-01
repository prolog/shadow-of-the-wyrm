#include "gtest/gtest.h"

CreaturePtr create_creature_with_weapon_and_15_str();

CreaturePtr create_creature_with_weapon_and_15_str()
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_strength(15);

  ItemPtr weapon_item = ItemPtr(new MeleeWeapon());

  Damage damage(3,4,2,DAMAGE_TYPE_SLASH, false, false, 0, {});

  WeaponPtr weapon = std::dynamic_pointer_cast<Weapon>(weapon_item);
  weapon->set_damage(damage);

  creature->get_equipment().set_item(weapon_item, EQUIPMENT_WORN_WIELDED);

  return creature;
}

TEST(SL_World_Calculators_PhysicalDamageCalculator, calculate_base_damage_object)
{
  PhysicalDamageCalculator pdc(ATTACK_TYPE_MELEE_PRIMARY);
  CreaturePtr creature = create_creature_with_weapon_and_15_str();

  // The base damage object should just be the weapon's damage.
  Damage base_damage = pdc.calculate_base_damage_object(creature);
  WeaponPtr weapon = std::dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_WIELDED));
  Damage expected_damage = weapon->get_damage();

  EXPECT_EQ(expected_damage, base_damage);
}

TEST(SL_World_Calculators_PhysicalDamageCalculator, calculate_base_damage_with_bonuses)
{
  PhysicalDamageCalculator pdc(ATTACK_TYPE_MELEE_PRIMARY);
  CreaturePtr creature = create_creature_with_weapon_and_15_str();

  Damage exp_base_damage = pdc.calculate_base_damage_object(creature);
  int bonus              = pdc.get_statistic_based_damage_modifier(creature);
  exp_base_damage.set_modifier(exp_base_damage.get_modifier() + bonus);

  EXPECT_EQ(exp_base_damage, pdc.calculate_base_damage_with_bonuses_or_penalties(creature));
}

// For every 5 points of Str > 10, +1 dam.
TEST(SL_World_Calculators_PhysicalDamageCalculator, get_statistic_based_damage_modifier)
{
  PhysicalDamageCalculator pdc(ATTACK_TYPE_MELEE_PRIMARY);

  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_strength(3);

  EXPECT_EQ(0, pdc.get_statistic_based_damage_modifier(creature));

  creature->set_strength(16);

  EXPECT_EQ(1, pdc.get_statistic_based_damage_modifier(creature));

  creature->set_strength(47);

  EXPECT_EQ(7, pdc.get_statistic_based_damage_modifier(creature));
}
