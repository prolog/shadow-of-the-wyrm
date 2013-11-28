#pragma once
#include "GardenGenerator.hpp"

class RockGardenGenerator : public GardenGenerator
{
  public:
    RockGardenGenerator(MapPtr new_base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width);

    virtual void generate() override;
};
