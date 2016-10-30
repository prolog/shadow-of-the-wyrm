#pragma once
#include "Directions.hpp"

// Parameters for generating a building in a squalid camp, a village, a city, etc.
class BuildingGenerationParameters
{
  public:
    BuildingGenerationParameters(const int new_start_row, const int new_end_row, const int new_start_col, const int new_end_col, const CardinalDirection new_door_direction, const bool new_multi_story);

    int get_start_row() const;
    int get_end_row() const;
    int get_start_col() const;
    int get_end_col() const;
    CardinalDirection get_door_direction() const;
    bool get_multi_story() const;

  protected:
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    CardinalDirection door_direction;
    bool multi_story;
};
