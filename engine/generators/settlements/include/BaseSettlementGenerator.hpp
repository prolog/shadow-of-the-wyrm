#pragma once
#include <vector>
#include "Generator.hpp"
#include "Building.hpp"
#include "BuildingGenerationParameters.hpp"
#include "GardenTypes.hpp"

class BaseSettlementGenerator : public SOTW::Generator
{
  public:
    BaseSettlementGenerator(MapPtr new_base_map);
    BaseSettlementGenerator(MapPtr new_base_map, const int growth_rate);
    
    virtual MapPtr generate(const Dimensions& dim)  override = 0;
    virtual MapPtr generate() override = 0;

  protected:
    virtual bool get_permanence_default() const override;
    virtual int get_pct_chance_shop() const;

    virtual void generate_shop_if_necessary(MapPtr map);

    virtual bool does_building_overlap(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const int offset_extra = 0);
    virtual bool does_tile_overlap(MapPtr map, const int row, const int col);

    bool is_rows_and_cols_in_range(const Dimensions& dim, const int start_row, const int end_row, const int start_col, const int end_col);
    bool generate_garden_if_possible(MapPtr map, const GardenType garden_type, const int start_row, const int end_row, const int start_col, const int end_col);
    bool generate_building_if_possible(MapPtr map, const BuildingGenerationParameters& bgp);
    std::pair<int, int> get_door_location(const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection direction);

    void generate_road_north(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_road_south(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_road_east(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_road_west(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);

    bool get_ignore_creature_generation_level_checks() const override;

    MapPtr base_map;
    int growth_rate;

    const int PROBABILITY_DECREMENT;
    const int BUILDING_PROBABILITY;
    const int MIN_BLOCK_SIZE;
    const int BLOCK_SIZE;
    const int NS_DIVISOR;
    const int EW_DIVISOR;

    std::vector<Building> buildings;
};
