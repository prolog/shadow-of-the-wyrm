#include "gtest/gtest.h"
#include "FieldGenerator.hpp"

TEST(SW_Engine_Calculators_OverworldMapDangerLevelCalculator, calculate_danger_level)
{
  Dimensions dim;
  FieldGenerator generator("test!");
  MapPtr map = generator.generate(dim);
  MapPtr map2 = generator.generate(dim);
  map->set_danger(17);
  OverworldMapDangerLevelCalculator calc;

  EXPECT_EQ(17, calc.calculate(map, map2));
}
