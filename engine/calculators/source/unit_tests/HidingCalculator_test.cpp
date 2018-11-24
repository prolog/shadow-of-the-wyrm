#include "gtest/gtest.h"
#include "MobileDecisionStrategy.hpp"

TEST(SW_Engine_Calculators_HidingCalculator, calculate_pct_chance_hide)
{
  HidingCalculator hc;
  CreaturePtr creature;
  CreaturePtr viewing_creature;
  MapPtr map;

  EXPECT_EQ(0, hc.calculate_pct_chance_hide(creature, map, TimeOfDayType::TIME_OF_DAY_UNDEFINED));

  Dimensions dim;
  map = std::make_shared<Map>(dim);

  creature = std::make_shared<Creature>();
  creature->set_id("cr1");

  EXPECT_EQ(100, hc.calculate_pct_chance_hide(creature, map, TimeOfDayType::TIME_OF_DAY_UNDEFINED));
}

