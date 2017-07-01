#include "gtest/gtest.h"
#include "DungeonGenerator.hpp"
TEST(SW_Engine_Calculators_DepthBasedDangerLevelCalculator, calculate_danger_level)
{
  Depth depth(10, 0, 10, 1);
  Depth depth2(13, 0, 13, 1);
  Dimensions dim;
  dim.set_depth(depth);

  MapPtr map = std::make_shared<Map>(dim);

  dim.set_depth(depth2);

  MapPtr map2 = std::make_shared<Map>(dim);

  if (map && map2)
  {
    map->set_danger(4);
    DepthBasedDangerLevelCalculator calc(ExitMovementType::EXIT_MOVEMENT_DESCEND);
    int calculated = calc.calculate(map, map2);

    EXPECT_EQ(7, calculated);
  }
}
