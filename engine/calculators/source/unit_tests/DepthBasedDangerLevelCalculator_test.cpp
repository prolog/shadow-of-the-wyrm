#include "gtest/gtest.h"
#include "DungeonGenerator.hpp"

// This case is essentially for most depth-based danger - dungeons, sewers,
// that sort of thing.
TEST(SW_Engine_Calculators_DepthBasedDangerLevelCalculator, calculate_danger_level_underworld)
{
  Depth depth(10, 0, 20, 1);
  Depth depth2(13, 5, 30, 1);
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

  // When the current depth isn't valid, in the context of the new depth,
  // the current depth should get defaulted to the minimum or maximum of the 
  // new depth, and the delta calculated correspondingly.
  //
  // In this case:
  //
  // - Base current depth should be the minimum of the new depth
  // - Delta should therefore be 13 - 5 = 8
  // - New danger should be current danger (4) + delta (8) = 12
  Depth depth_base(0,0,0,1);
  dim.set_depth(depth_base);

  map = std::make_shared<Map>(dim);
  map->set_danger(4);
  calculated = calc.calculate(map, map2);

  EXPECT_EQ(12, calculated);
}

// This case covers the endgame floating tower
TEST(SW_Engine_Calculators_DepthBasedDangerLevelCalculator, calculate_danger_level_overworld)
{
  Depth depth(-10, -20, 0, 7);
  Depth depth2(-17, -20, 0, 7);

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
