#include "gtest/gtest.h"
#include "DungeonGenerator.hpp"

// This case is essentially for most depth-based danger - dungeons, sewers,
// that sort of thing.
TEST(SW_Engine_Calculators_DepthBasedDangerLevelCalculator, calculate_danger_level_underworld)
{
  Depth depth(10, 0, 10, 1);
  Depth depth2(13, 0, 13, 1);
  Dimensions dim;
  dim.set_depth(depth);

  MapPtr map = std::make_shared<Map>(dim);

  dim.set_depth(depth2);

  MapPtr map2 = std::make_shared<Map>(dim);

  map->set_danger(4);
  DepthBasedDangerLevelCalculator calc(ExitMovementType::EXIT_MOVEMENT_DESCEND);
  int calculated = calc.calculate(map, map2);

  EXPECT_EQ(7, calculated);

  // Back up the dungeon...
  map2->set_danger(7);
  DepthBasedDangerLevelCalculator calc2(ExitMovementType::EXIT_MOVEMENT_ASCEND);
  calculated = calc2.calculate(map2, map);

  EXPECT_EQ(4, calculated);
}

// This case covers the endgame floating tower
TEST(SW_Engine_Calculators_DepthBasedDangerLevelCalculator, calculate_danger_level_overworld)
{
  Depth depth(-10, -10, -10, 7);
  Depth depth2(-17, -17, -17, 7);

  Dimensions dim;
  dim.set_depth(depth);

  MapPtr map = std::make_shared<Map>(dim);

  dim.set_depth(depth2);

  MapPtr map2 = std::make_shared<Map>(dim);

  map->set_danger(3);
  DepthBasedDangerLevelCalculator calc(ExitMovementType::EXIT_MOVEMENT_ASCEND);
  int calculated = calc.calculate(map, map2);

  EXPECT_EQ(10, calculated);

  // Back down the tower...
  map2->set_danger(10);
  DepthBasedDangerLevelCalculator calc2(ExitMovementType::EXIT_MOVEMENT_DESCEND);
  calculated = calc2.calculate(map2, map);

  EXPECT_EQ(3, calculated);
}
