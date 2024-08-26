#pragma once
#include "DangerLevelCalculator.hpp"

class WorldMapDangerLevelCalculator : public DangerLevelCalculator
{
  public:
    int calculate(MapPtr old_map, MapPtr new_map) const override;

    // Get the max distance from the given (starting) coordinate to the
    // edges of the map.
    int get_max_distance(const Coordinate& starting_location, const int map_max_y, const int map_max_x) const;
};

