#pragma once
#include "GardenGenerator.hpp"

// Generates a shade garden: surrounded by trees, with shady plants
// and a bench in the centre.
class ShadeGardenGenerator : public GardenGenerator
{
  public:
    ShadeGardenGenerator(MapPtr map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width);

    void generate();
    void generate_tree_cover();
    void generate_plants();
    void generate_features();    
};
