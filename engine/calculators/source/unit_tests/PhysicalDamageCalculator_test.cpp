#include "gtest/gtest.h"

CreaturePtr create_creature_with_weapon_and_15_str();

CreaturePtr create_creature_with_weapon_and_15_str()
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_strength(15);

  ItemPtr weapon_item = ItemPtr(new MeleeWeapon());

  Damage damage(3,4,2,DamageType::DAMAGE_TYPE_SLASH, {}, false, false, false, false, 0, {});

  WeaponPtr weapon = std::dynamic_pointer_cast<Weapon>(weapon_item);
  weapon->set_damage(damage);

  creature->get_equipment().set_item(weapon_item, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  return creature;
}

TEST(SW_World_Calculators_PhysicalDamageCalculator, calculate_base_damage_object)
{
  PhysicalDamageCalculator pdc(AttackType::ATTACK_TYPE_MELEE_PRIMARY, PhaseOfMoonType::PHASE_OF_MOON_NEW);
  CreaturePtr creature = create_creature_with_weapon_and_15_str();
  Statistic addl_creature_damage(10);
  creature->set_addl_damage(addl_creature_damage);

  // The base damage object should just be the weapon's damage.
  Damage base_damage = pdc.calculate_base_damage_object(creature);
  WeaponPtr weapon = std::dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));
  Damage expected_damage = weapon->get_damage();

  // Should exclude the creature's add'l damage - that will be accounted for
  // in the bonuses/penalties.
  EXPECT_EQ(expected_damage, base_damage);
}

TEST(SW_World_Calculators_PhysicalDamageCalculator, calculate_base_damage_with_bonuses)
{
  PhysicalDamageCalculator pdc(AttackType::ATTACK_TYPE_MELEE_PRIMARY, PhaseOfMoonType::PHASE_OF_MOON_NEW);
  CreaturePtr creature = create_creature_with_weapon_and_15_str();
  Statistic addl_creature_damage(10);
  creature->set_addl_damage(addl_creature_damage);

  Damage exp_base_damage = pdc.calculate_base_damage_object(creature);
  int bonus              = pdc.get_statistic_based_damage_modifier(creature);
  bonus += creature->get_addl_damage().get_current();
  exp_base_damage.set_modifier(exp_base_damage.get_modifier() + bonus);

  EXPECT_EQ(exp_base_damage, pdc.calculate_base_damage_with_bonuses_or_penalties(creature));
}

// For every 5 points of Str > 10, +1 dam.
TEST(SW_World_Calculators_PhysicalDamageCalculator, get_statistic_based_damage_modifier)
{
  PhysicalDamageCalculator pdc(AttackType::ATTACK_TYPE_MELEE_PRIMARY, PhaseOfMoonType::PHASE_OF_MOON_NEW);

  CreaturePtr creature = std::make_shared<Creature>();
  creature->set_strength(3);

  EXPECT_EQ(0, pdc.get_statistic_based_damage_modifier(creature));

  creature->set_strength(16);

  EXPECT_EQ(1, pdc.get_statistic_based_damage_modifier(creature));

  creature->set_strength(47);

  EXPECT_EQ(7, pdc.get_statistic_based_damage_modifier(creature));
}

// For every 0.02 BAC, +1 dam.
TEST(SW_World_Calculators_PhysicalDamageCalculator, get_drunkenness_modifier)
{
  PhysicalDamageCalculator pdc(AttackType::ATTACK_TYPE_MELEE_PRIMARY, PhaseOfMoonType::PHASE_OF_MOON_NEW);
  CreaturePtr creature = create_creature_with_weapon_and_15_str();

  Blood b;
  b.set_litres(5);
  b.set_grams_alcohol(1);

  creature->set_blood(b);

  Damage exp_base_damage = pdc.calculate_base_damage_object(creature);
  int bonus = pdc.get_statistic_based_damage_modifier(creature);
  int dr_bonus = static_cast<int>(creature->get_blood().get_blood_alcohol_content() * 100) / 2;
  exp_base_damage.set_modifier(exp_base_damage.get_modifier() + bonus + dr_bonus);

  EXPECT_EQ(exp_base_damage, pdc.calculate_base_damage_with_bonuses_or_penalties(creature));

  // Go from 0.02 to 0.06, or +2 additional damage.
  b.set_grams_alcohol(3);
  creature->set_blood(b);

  exp_base_damage.set_modifier(exp_base_damage.get_modifier() + 2);

  EXPECT_EQ(exp_base_damage, pdc.calculate_base_damage_with_bonuses_or_penalties(creature));
}