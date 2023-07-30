#include "gtest/gtest.h"

TEST(SW_Engine_Strings_DirectionLocationTextKeys, get_direction_location_sid)
{
  std::map<Direction, std::string> dirs = {{Direction::DIRECTION_NORTH, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH},
                                           {Direction::DIRECTION_NORTH_WEST, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_WEST},
                                           {Direction::DIRECTION_NORTH_EAST, DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_EAST},
                                           {Direction::DIRECTION_WEST, DirectionLocationTextKeys::DIRECTION_LOCATION_WEST},
                                           {Direction::DIRECTION_EAST, DirectionLocationTextKeys::DIRECTION_LOCATION_EAST},
                                           {Direction::DIRECTION_SOUTH, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH},
                                           {Direction::DIRECTION_SOUTH_WEST, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_WEST},
                                           {Direction::DIRECTION_SOUTH_EAST, DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_EAST}};

  for (const auto& l_pair : dirs)
  {
    EXPECT_EQ(l_pair.second, DirectionLocationTextKeys::get_direction_location_sid(l_pair.first));
  }
}

