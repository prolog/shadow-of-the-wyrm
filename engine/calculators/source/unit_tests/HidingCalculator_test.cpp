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

  viewing_creature = std::make_shared<Creature>();
  DecisionStrategyPtr dec = std::make_shared<MobileDecisionStrategy>(nullptr);
  viewing_creature->set_id("cr2");
  viewing_creature->set_decision_strategy(dec);
  MapPtr fov_map = std::make_shared<Map>(dim);
  dec->set_fov_map(fov_map);
  fov_map->add_creature(creature);

  map->add_creature(viewing_creature);

  EXPECT_EQ(1, hc.calculate_pct_chance_hide(creature, map, TimeOfDayType::TIME_OF_DAY_UNDEFINED));
}

