#pragma once
#include "MapDisplayArea.hpp"
#include "Map.hpp"

// Class for calculating the location of the creature on the display.
class CreatureCoordinateCalculator
{
  public:
    static Coordinate calculate_engine_coordinate(const MapDisplayArea& display_area, MapPtr current_map, const Coordinate& reference_coords);
    static Coordinate calculate_display_coordinate(const MapDisplayArea& display_area, MapPtr current_map, const Coordinate& reference_coords);
};

