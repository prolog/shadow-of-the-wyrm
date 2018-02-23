#pragma once
#include "BuildingGenerationParameters.hpp"
#include "Building.hpp"
#include "Directions.hpp"
#include "GardenTypes.hpp"
#include "Map.hpp"

class SettlementGeneratorUtils
{
  public:
    static std::pair<int, int> get_door_location(const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection direction);
    static bool does_building_overlap(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const int offset_extra = 0);
    static bool does_tile_overlap(MapPtr map, const int row, const int col);
    static bool is_rows_and_cols_in_range(const Dimensions& dim, const int start_row, const int end_row, const int start_col, const int end_col);
    static bool generate_garden_if_possible(MapPtr map, const GardenType garden_type, const int start_row, const int end_row, const int start_col, const int end_col);
    static bool generate_building_if_possible(MapPtr map, const BuildingGenerationParameters& bgp, std::vector<Building>& buildings, const int growth_rate);

  protected:
    SettlementGeneratorUtils();
    ~SettlementGeneratorUtils();
};