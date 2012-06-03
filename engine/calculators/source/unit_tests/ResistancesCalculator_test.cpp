#include "gtest/gtest.h"

TEST(SL_Engine_Calcalators_ResistancesCalculator, calculate_resistances)
{
  RacePtr racep = RacePtr(new Race());
  ClassPtr classp = ClassPtr(new Class());

  // JCD FIXME: Update this for creature equipment, later!
  Creature creature;

  Resistances race_resists;
  Resistances class_resists;

  race_resists.set_resistance_value(DAMAGE_TYPE_SLASH, 0.15);
  race_resists.set_resistance_value(DAMAGE_TYPE_HOLY, 0.20);
  race_resists.set_resistance_value(DAMAGE_TYPE_POISON, 0.10);
  race_resists.set_resistance_value(DAMAGE_TYPE_LIGHTNING, 0.25);

  class_resists.set_resistance_value(DAMAGE_TYPE_SLASH, 0.05);
  class_resists.set_resistance_value(DAMAGE_TYPE_HOLY, 0.05);
  class_resists.set_resistance_value(DAMAGE_TYPE_POISON, 0.05);
  class_resists.set_resistance_value(DAMAGE_TYPE_LIGHTNING, 0.05);

  racep->set_resistances(race_resists);
  classp->set_resistances(class_resists);

  Resistances calc_resists = ResistancesCalculator::calculate_resistances(creature, racep, classp);

  EXPECT_DOUBLE_EQ(0.80, calc_resists.get_resistance_value(DAMAGE_TYPE_SLASH));
  EXPECT_DOUBLE_EQ(0.75, calc_resists.get_resistance_value(DAMAGE_TYPE_HOLY));
  EXPECT_DOUBLE_EQ(0.85, calc_resists.get_resistance_value(DAMAGE_TYPE_POISON));
  EXPECT_DOUBLE_EQ(0.70, calc_resists.get_resistance_value(DAMAGE_TYPE_LIGHTNING));
}
