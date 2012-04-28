#pragma once
#include "BaseSettlementGenerator.hpp"

class HamletGenerator : public BaseSettlementGenerator
{
  public:
    HamletGenerator(MapPtr new_base_map);
    HamletGenerator(MapPtr new_base_map, const int growth_rate);

    virtual MapPtr generate(const Dimensions& dim);
    virtual MapPtr generate();
    
  protected:
    // Generates an E-W road.
    void generate_road(MapPtr map, const int road_start_col, const int road_end_col, const int road_row, const int increment);
    void generate_circular_hamlet(MapPtr map);
    
    void generate_core_hamlet_buildings(MapPtr map, const int circle_row, const int circle_col, const int hamlet_size);
    void generate_additional_random_buildings(MapPtr map, const int road_row, const int road_col, const int road_end_col);    
    
    bool potentially_generate_vegetable_garden(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const int probability);
    
    void initialize_constants();
    
    // Dimensions for gardens and buildings:
    int BUILDING_HEIGHT_MIN;
    int BUILDING_HEIGHT_MAX;
    int BUILDING_WIDTH_MIN;
    int BUILDING_WIDTH_MAX;
    
    int GARDEN_HEIGHT_MIN;
    int GARDEN_HEIGHT_MAX;
    int GARDEN_WIDTH_MIN;
    int GARDEN_WIDTH_MAX;
};
