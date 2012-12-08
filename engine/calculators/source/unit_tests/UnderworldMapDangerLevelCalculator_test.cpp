#include "gtest/gtest.h"
#include "DungeonGenerator.hpp"
TEST(SL_Engine_Calculators_UnderworldMapDangerLevelCalculator, calculate_danger_level)
{
  Depth depth(10, 10);
  Depth depth2(13, 13);
  Dimensions dim;
  dim.set_depth(depth);
  DungeonGenerator generator("test");
  MapPtr map = generator.generate(dim);

  dim.set_depth(depth2);

  MapPtr map2 = generator.generate(dim);
  map->set_danger(4);
  UnderworldMapDangerLevelCalculator calc;

  EXPECT_EQ(7, calc.calculate(map, map2));
}
