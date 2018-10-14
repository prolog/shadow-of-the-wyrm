#pragma once
#include <string>
#include <vector>
#include "ClassIdentifiers.hpp"
#include "Directions.hpp"

// Parameters for generating a building in a squalid camp, a village, a city, etc.
class BuildingGenerationParameters
{
  public:
    BuildingGenerationParameters(const int new_start_row, const int new_end_row, const int new_start_col, const int new_end_col, const CardinalDirection new_door_direction, const bool new_multi_story, const std::vector<ClassIdentifier>& features, const std::vector<std::string>& item_ids);

    int get_start_row() const;
    int get_end_row() const;
    int get_start_col() const;
    int get_end_col() const;
    CardinalDirection get_door_direction() const;
    bool get_multi_story() const;
    std::vector<ClassIdentifier> get_features() const;
    std::vector<std::string> get_item_ids() const;

  protected:
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    CardinalDirection door_direction;
    bool multi_story;
    std::vector<ClassIdentifier> features;
    std::vector<std::string> item_ids;
};
