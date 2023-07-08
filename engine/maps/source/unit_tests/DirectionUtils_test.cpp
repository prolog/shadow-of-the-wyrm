#include <utility>
#include <map>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

TEST(SW_Engine_Maps_DirectionUtils, is_zlevel)
{
  EXPECT_FALSE(DirectionUtils::is_zlevel(Direction::DIRECTION_NORTH));
  EXPECT_FALSE(DirectionUtils::is_zlevel(Direction::DIRECTION_SOUTH));
  EXPECT_FALSE(DirectionUtils::is_zlevel(Direction::DIRECTION_EAST));
  EXPECT_FALSE(DirectionUtils::is_zlevel(Direction::DIRECTION_WEST));
  EXPECT_FALSE(DirectionUtils::is_zlevel(Direction::DIRECTION_NORTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_zlevel(Direction::DIRECTION_NORTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_zlevel(Direction::DIRECTION_UP));
  EXPECT_TRUE(DirectionUtils::is_zlevel(Direction::DIRECTION_DOWN));
}

TEST(SW_Engine_Maps_DirectionUtils, is_cardinal)
{
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_NORTH));
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_SOUTH));
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_EAST));
  EXPECT_TRUE(DirectionUtils::is_cardinal(Direction::DIRECTION_WEST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(Direction::DIRECTION_NORTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(Direction::DIRECTION_NORTH_WEST));
  EXPECT_FALSE(DirectionUtils::is_cardinal(Direction::DIRECTION_UP));
}

TEST(SW_Engine_Maps_DirectionUtils, is_ordinal)
{
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_NORTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_NORTH_EAST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_SOUTH_WEST));
  EXPECT_TRUE(DirectionUtils::is_ordinal(Direction::DIRECTION_SOUTH_EAST));
  EXPECT_FALSE(DirectionUtils::is_ordinal(Direction::DIRECTION_NORTH));
  EXPECT_FALSE(DirectionUtils::is_ordinal(Direction::DIRECTION_DOWN));
}

TEST(SW_Engine_Maps_DirectionUtils, to_direction)
{
  EXPECT_EQ(Direction::DIRECTION_NULL, DirectionUtils::to_direction(CardinalDirection::CARDINAL_DIRECTION_NULL));
  EXPECT_EQ(Direction::DIRECTION_SOUTH, DirectionUtils::to_direction(CardinalDirection::CARDINAL_DIRECTION_SOUTH));
  EXPECT_EQ(Direction::DIRECTION_WEST, DirectionUtils::to_direction(CardinalDirection::CARDINAL_DIRECTION_WEST));
  EXPECT_EQ(Direction::DIRECTION_NORTH, DirectionUtils::to_direction(CardinalDirection::CARDINAL_DIRECTION_NORTH));
  EXPECT_EQ(Direction::DIRECTION_EAST, DirectionUtils::to_direction(CardinalDirection::CARDINAL_DIRECTION_EAST));
}

TEST(SW_Engine_Maps_DirectionUtils, get_opposite_direction)
{
  EXPECT_EQ(Direction::DIRECTION_SOUTH_EAST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NORTH_WEST));
  EXPECT_EQ(Direction::DIRECTION_SOUTH, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NORTH));
  EXPECT_EQ(Direction::DIRECTION_SOUTH_WEST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NORTH_EAST));
  EXPECT_EQ(Direction::DIRECTION_EAST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_WEST));
  EXPECT_EQ(Direction::DIRECTION_NULL, DirectionUtils::get_opposite_direction(Direction::DIRECTION_NULL));
  EXPECT_EQ(Direction::DIRECTION_WEST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_EAST));
  EXPECT_EQ(Direction::DIRECTION_NORTH_EAST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_SOUTH_WEST));
  EXPECT_EQ(Direction::DIRECTION_NORTH, DirectionUtils::get_opposite_direction(Direction::DIRECTION_SOUTH));
  EXPECT_EQ(Direction::DIRECTION_NORTH_WEST, DirectionUtils::get_opposite_direction(Direction::DIRECTION_SOUTH_EAST));
  EXPECT_EQ(Direction::DIRECTION_UP, DirectionUtils::get_opposite_direction(Direction::DIRECTION_DOWN));
  EXPECT_EQ(Direction::DIRECTION_DOWN, DirectionUtils::get_opposite_direction(Direction::DIRECTION_UP));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_SOUTH, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_NORTH));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_NORTH, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_SOUTH));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_EAST, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_WEST));
  EXPECT_EQ(CardinalDirection::CARDINAL_DIRECTION_WEST, DirectionUtils::get_opposite_direction(CardinalDirection::CARDINAL_DIRECTION_EAST));
}

TEST(SW_Engine_Maps_DirectionUtils, direction_matches_category)
{
  // First bool = is cardinal?
  // Second bool = is cardinal or ordinal?
  vector<pair<Direction, pair<bool, bool>>> dirs = 
  {
    { Direction::DIRECTION_NORTH_WEST,{ false, true } },
    { Direction::DIRECTION_NORTH,{ true, true } },
    { Direction::DIRECTION_NORTH_EAST,{ false, true } },
    { Direction::DIRECTION_WEST,{ true, true } },
    { Direction::DIRECTION_NULL,{ true, true } },
    { Direction::DIRECTION_EAST,{ true, true } },
    { Direction::DIRECTION_SOUTH_WEST,{ false, true } },
    { Direction::DIRECTION_SOUTH,{ true, true } },
    { Direction::DIRECTION_SOUTH_EAST,{ false, true } },
    { Direction::DIRECTION_UP,{ false, false } },
    { Direction::DIRECTION_DOWN,{ false, false } }
  };

  for (auto& dir_pair : dirs)
  {
    EXPECT_EQ(dir_pair.second.first, DirectionUtils::direction_matches_category(dir_pair.first, DirectionCategory::DIRECTION_CATEGORY_CARDINAL));
    EXPECT_EQ(dir_pair.second.second, DirectionUtils::direction_matches_category(dir_pair.first, DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL));
  }
}

TEST(SW_Engine_Maps_DirectionUtils, get_perpendicular_directions)
{
  EXPECT_EQ(vector<CardinalDirection>({}), DirectionUtils::get_perpendicular_directions(CardinalDirection::CARDINAL_DIRECTION_NULL));

  vector<CardinalDirection> dirs = {CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH};
  EXPECT_EQ(dirs, DirectionUtils::get_perpendicular_directions(CardinalDirection::CARDINAL_DIRECTION_EAST));
  EXPECT_EQ(dirs, DirectionUtils::get_perpendicular_directions(CardinalDirection::CARDINAL_DIRECTION_WEST));

  dirs = {CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST};
  EXPECT_EQ(dirs, DirectionUtils::get_perpendicular_directions(CardinalDirection::CARDINAL_DIRECTION_NORTH));
  EXPECT_EQ(dirs, DirectionUtils::get_perpendicular_directions(CardinalDirection::CARDINAL_DIRECTION_SOUTH));
}

TEST(SW_Engine_Maps_DirectionUtils, to_cardinal_direction)
{
  map<vector<Direction>, CardinalDirection> mapping = {{{Direction::DIRECTION_NORTH, Direction::DIRECTION_NORTH_EAST, Direction::DIRECTION_NORTH_WEST}, CardinalDirection::CARDINAL_DIRECTION_NORTH},
                                                       {{Direction::DIRECTION_WEST}, CardinalDirection::CARDINAL_DIRECTION_WEST},
                                                       {{Direction::DIRECTION_EAST}, CardinalDirection::CARDINAL_DIRECTION_EAST},
                                                       {{Direction::DIRECTION_SOUTH, Direction::DIRECTION_SOUTH_EAST, Direction::DIRECTION_SOUTH_WEST}, CardinalDirection::CARDINAL_DIRECTION_SOUTH}};
  for (auto m_it : mapping)
  {
    vector<Direction> vd = m_it.first;

    for (auto d : vd)
    {
      EXPECT_EQ(m_it.second, DirectionUtils::to_cardinal_direction(d));
    }
  }
}

TEST(SW_Engine_Maps_DirectionUtils, get_in_map_dirs)
{
  vector<Direction> dirs = { Direction::DIRECTION_NORTH_WEST, Direction::DIRECTION_NORTH, Direction::DIRECTION_NORTH_EAST, Direction::DIRECTION_WEST, Direction::DIRECTION_EAST, Direction::DIRECTION_SOUTH_WEST, Direction::DIRECTION_SOUTH, Direction::DIRECTION_SOUTH_EAST };
  vector<Direction> move_dirs = DirectionUtils::get_in_map_movement_directions();

  EXPECT_EQ(move_dirs.size(), dirs.size());

  for (const auto d : dirs)
  {
    EXPECT_TRUE(std::find(move_dirs.begin(), move_dirs.end(), d) != move_dirs.end());
  }
}
