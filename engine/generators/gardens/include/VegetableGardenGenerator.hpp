#pragma once
#include "GardenGenerator.hpp"

class VegetableGardenGenerator : public GardenGenerator
{
  public:
    VegetableGardenGenerator(MapPtr base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width);

    virtual void generate();

  protected:
    void populate_vegetable_map();
    
    void plant_vegetables();
    
    std::map<int, std::string> vegetable_map;
    int vegetable_min;
    int vegetable_max;
};
