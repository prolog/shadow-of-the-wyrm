#include "Ring.hpp"
#include "Armour.hpp"
#include "gtest/gtest.h"

TEST(SL_Engine_Calcalators_ResistancesCalculator, calculate_resistances)
{
  RacePtr racep = std::make_shared<Race>();
  ClassPtr classp = std::make_shared<Class>();

  CreaturePtr creature = CreaturePtr(new Creature());

  Resistances race_resists;
  Resistances class_resists;
  Resistances intrinsic_resists;

  race_resists.set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 0.15);
  race_resists.set_resistance_value(DamageType::DAMAGE_TYPE_HOLY, 0.20);
  race_resists.set_resistance_value(DamageType::DAMAGE_TYPE_POISON, 0.10);
  race_resists.set_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING, 0.25);

  class_resists.set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 0.05);
  class_resists.set_resistance_value(DamageType::DAMAGE_TYPE_HOLY, 0.05);
  class_resists.set_resistance_value(DamageType::DAMAGE_TYPE_POISON, 0.05);
  class_resists.set_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING, 0.05);

  intrinsic_resists.set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 0.10);
  intrinsic_resists.set_resistance_value(DamageType::DAMAGE_TYPE_HOLY, 0.02);
  intrinsic_resists.set_resistance_value(DamageType::DAMAGE_TYPE_POISON, 0.04);
  intrinsic_resists.set_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING, 0.07);

  racep->set_resistances(race_resists);
  classp->set_resistances(class_resists);

  creature->set_intrinsic_resistances(intrinsic_resists);

  ResistancesCalculator rc;
  Resistances calc_resists = rc.calculate_resistances(creature, racep, classp);

  EXPECT_DOUBLE_EQ(0.70, calc_resists.get_resistance_value(DamageType::DAMAGE_TYPE_SLASH));
  EXPECT_DOUBLE_EQ(0.73, calc_resists.get_resistance_value(DamageType::DAMAGE_TYPE_HOLY));
  EXPECT_DOUBLE_EQ(0.81, calc_resists.get_resistance_value(DamageType::DAMAGE_TYPE_POISON));
  EXPECT_DOUBLE_EQ(0.63, calc_resists.get_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING));
}

TEST(SL_Engine_Calcalators_ResistancesCalculator, calculate_equipment_resistances)
{
  CreaturePtr creature = CreaturePtr(new Creature());

  ItemPtr item = ItemPtr(new Ring());
  ItemPtr item2 = ItemPtr(new Armour());

  Resistances i1resist;
  i1resist.set_all_resistances_to(0);
  i1resist.set_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING, -0.35);
  i1resist.set_resistance_value(DamageType::DAMAGE_TYPE_ARCANE, 0.04);
  item->set_resistances(i1resist);

  Resistances i2resist;
  i2resist.set_all_resistances_to(0);
  i2resist.set_resistance_value(DamageType::DAMAGE_TYPE_SLASH, 0.20);
  i2resist.set_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING, 0.10);
  i2resist.set_resistance_value(DamageType::DAMAGE_TYPE_ARCANE, 0.14);
  item2->set_resistances(i2resist);

  Equipment& eq = creature->get_equipment();
  eq.set_item(item2, EquipmentWornLocation::EQUIPMENT_WORN_HEAD);
  eq.set_item(item, EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER);

  ResistancesCalculator rc;
  RacePtr nullrace;
  ClassPtr nullclass;
  Resistances calc_resist = rc.calculate_resistances(creature, nullrace, nullclass);

  EXPECT_DOUBLE_EQ(1.25, calc_resist.get_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING));
  EXPECT_DOUBLE_EQ(0.80, calc_resist.get_resistance_value(DamageType::DAMAGE_TYPE_SLASH));
  EXPECT_DOUBLE_EQ(0.82, calc_resist.get_resistance_value(DamageType::DAMAGE_TYPE_ARCANE));
}