#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_FieldCalculator, pct_chance_wild_grain)
{
  FieldCalculator fc;
  CreaturePtr creature;

  Coordinate c = {0,0};
  std::map<int, int> row_and_pct = { {0, 0}, { 12, 12 }, {36, 36 }, {64, 36}, {88, 12}, {100, 0} };

  // Base case: ignore creature, entirely based on how close we are to the
  // equator.
  for (const auto& r : row_and_pct)
  {
    c.first = r.first;

    EXPECT_EQ(r.second, fc.calc_pct_chance_wild_grains(creature, 100, c));
  }

  // Foraging case: should be the max of the equator distance-based value and
  // the creature's Foraging skill.
  creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_FORAGING, 30);

  EXPECT_EQ(30, fc.calc_pct_chance_wild_grains(creature, 100, { 0, 0 }));
  EXPECT_EQ(30, fc.calc_pct_chance_wild_grains(creature, 100, { 25, 0 }));
  EXPECT_EQ(42, fc.calc_pct_chance_wild_grains(creature, 100, { 58, 0 }));
}

