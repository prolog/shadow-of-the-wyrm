#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WorldMapDangerLevelCalculator, calculate)
{
  WorldMapDangerLevelCalculator wmdlc;

  Dimensions dim1(50, 100);
  MapPtr map1 = std::make_shared<Map>(dim1);
  const Coordinate start = { 3,2 };
  vector<Coordinate> cur_p_locs = { {36, 12}, {5, 5}, {26, 1} };

  for (const Coordinate& p_loc : cur_p_locs)
  {
    map1->add_or_update_location(WorldMapLocationTextKeys::STARTING_LOCATION, start);
    map1->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, p_loc);

    int distance = CoordUtils::chebyshev_distance(start, p_loc);
    float danger_calc = (distance /
                        (static_cast<float>(wmdlc.get_max_distance(start, map1->size().get_y(), map1->size().get_x()))));
    int exp_value = static_cast<int>(danger_calc * CreatureConstants::MAX_CREATURE_LEVEL);

    EXPECT_EQ(exp_value, wmdlc.calculate(map1, nullptr /* the second map is unused in this class' overload */));
  }
}

TEST(SW_Engine_Calculators_WorldMapDangerLevelCalculator, get_max_distance)
{
  Coordinate c = { 0, 0 };
  WorldMapDangerLevelCalculator wmc;

  EXPECT_EQ(10, wmc.get_max_distance(c, 10, 10));

  c = { 25, 13 };

  EXPECT_EQ(87, wmc.get_max_distance(c, 100, 100));

  c = { 36, 42 };

  EXPECT_EQ(64, wmc.get_max_distance(c, 100, 100));
}
