#include "BuildingGenerationParameters.hpp"

using namespace std;

BuildingGenerationParameters::BuildingGenerationParameters(const int new_start_row, const int new_end_row, const int new_start_col, const int new_end_col, const CardinalDirection new_door_direction, const bool new_multi_story, const vector<ClassIdentifier>& new_features, const vector<string>& new_creature_ids, const vector<string>& new_item_ids, const TileType new_wall_tile_type)
: start_row(new_start_row), end_row(new_end_row), start_col(new_start_col), end_col(new_end_col), door_direction(new_door_direction), multi_story(new_multi_story), features(new_features), creature_ids(new_creature_ids), item_ids(new_item_ids), wall_tile_type(new_wall_tile_type)
{
}

int BuildingGenerationParameters::get_start_row() const
{
  return start_row;
}

int BuildingGenerationParameters::get_end_row() const
{
  return end_row;
}

int BuildingGenerationParameters::get_start_col() const
{
  return start_col;
}

int BuildingGenerationParameters::get_end_col() const
{
  return end_col;
}

CardinalDirection BuildingGenerationParameters::get_door_direction() const
{
  return door_direction;
}

bool BuildingGenerationParameters::get_multi_story() const
{
  return multi_story;
}

vector<ClassIdentifier> BuildingGenerationParameters::get_features() const
{
  return features;
}

vector<string> BuildingGenerationParameters::get_creature_ids() const
{
  return creature_ids;
}

vector<string> BuildingGenerationParameters::get_item_ids() const
{
  return item_ids;
}

TileType BuildingGenerationParameters::get_wall_tile_type() const
{
  return wall_tile_type;
}