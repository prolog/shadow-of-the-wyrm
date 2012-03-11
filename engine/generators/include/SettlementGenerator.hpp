#pragma once
#include "Map.hpp"
#include "Directions.hpp"
#include "Generator.hpp"

class SettlementGenerator : public Generator
{
  public:
    SettlementGenerator(MapPtr new_base_map);
    SettlementGenerator(MapPtr new_base_map, const int growth_rate);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim, const std::string& map_exit_id);

  protected:
     MapPtr generate_roads_and_buildings(MapPtr map);
     MapPtr generate_settlement_with_square_and_cardinal_roads(MapPtr map);
     MapPtr generate_settlement_with_winding_road(MapPtr map);
     MapPtr populate_settlement(MapPtr map);

     MapPtr generate_square(MapPtr map, const int start_row, const int start_col, const int square_size);
     MapPtr generate_road_north(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0);
     MapPtr generate_road_south(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0);
     MapPtr generate_road_east(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0);
     MapPtr generate_road_west(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0);

     MapPtr generate_building_if_possible(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection door_direction);
     bool   does_building_overlap(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col);
     bool   does_tile_overlap(MapPtr map, const int row, const int col);

     // JCD FIXME: This can probably be moved into Generator.
     std::pair<int, int> get_door_location(const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection direction);

     const int GROWTH_RATE;
     const int PROBABILITY_DECREMENT;
     const int BUILDING_PROBABILITY;
     const int MIN_BLOCK_SIZE;
     const int BLOCK_SIZE;
     const int NS_DIVISOR;
     const int EW_DIVISOR;
     
     MapPtr base_map;
};

typedef boost::shared_ptr<SettlementGenerator> SettlementGeneratorPtr;
