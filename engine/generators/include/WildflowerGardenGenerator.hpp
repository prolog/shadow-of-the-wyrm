#pragma once
#include "GardenGenerator.hpp"

class WildflowerGardenGenerator : public GardenGenerator
{
  public:
    WildflowerGardenGenerator(MapPtr new_base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width);

    virtual void generate();
    
  protected:
    void initialize_generator();
    void populate_wildflower_ids();
    
    void seed_flowers();
    
    std::map<int, std::string> wildflower_item_ids;
    int wildflower_rand_min;
    int wildflower_rand_max;
};
