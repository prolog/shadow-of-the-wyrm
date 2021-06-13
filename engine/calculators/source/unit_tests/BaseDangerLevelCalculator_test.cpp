#include "gtest/gtest.h"
#include "FieldGenerator.hpp"

TEST(SW_Engine_Calculators_BaseDangerLevelCalculator, calculate_danger_level)
{
  Dimensions dim;
  FieldGenerator generator("test!");
  MapPtr map = generator.generate(dim);
  MapPtr map2 = generator.generate(dim);
  vector<int> dangers = {17, 3, 6, 45, 4, 2};

  for (int danger : dangers)
  {
    map->set_danger(danger);
    BaseDangerLevelCalculator calc;

    EXPECT_EQ(danger, calc.calculate(map, map2));
  }
}

