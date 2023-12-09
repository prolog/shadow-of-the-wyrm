#pragma once
#include <string>
#include "Directions.hpp"

class DirectionLocationTextKeys
{
  public:
    static const std::string get_direction_location_sid(const Direction dir);

    static const std::string DIRECTION_LOCATION_NORTH_WEST;
    static const std::string DIRECTION_LOCATION_NORTH;
    static const std::string DIRECTION_LOCATION_NORTH_EAST;
    static const std::string DIRECTION_LOCATION_WEST;
    static const std::string DIRECTION_LOCATION_MIDDLE;
    static const std::string DIRECTION_LOCATION_EAST;
    static const std::string DIRECTION_LOCATION_SOUTH_WEST;
    static const std::string DIRECTION_LOCATION_SOUTH;
    static const std::string DIRECTION_LOCATION_SOUTH_EAST;

  protected:
    DirectionLocationTextKeys();
    ~DirectionLocationTextKeys();
};