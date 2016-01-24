#include "gtest/gtest.h"
#include "DungeonGenerator.hpp"
TEST(SW_Engine_Calculators_UnderworldMapDangerLevelCalculator, calculate_danger_level)
{
  Depth depth(10, 10);
  Depth depth2(13, 13);
  Dimensions dim;
  dim.set_depth(depth);

  MapPtr map = std::make_shared<Map>(dim);

  dim.set_depth(depth2);

  MapPtr map2 = std::make_shared<Map>(dim);

  if (map && map2)
  {
    map->set_danger(4);
    UnderworldMapDangerLevelCalculator calc;
    int calculated = calc.calculate(map, map2);

    EXPECT_EQ(7, calculated);
  }
}
