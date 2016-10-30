#include "BuildingGenerationParameters.hpp"

BuildingGenerationParameters::BuildingGenerationParameters(const int new_start_row, const int new_end_row, const int new_start_col, const int new_end_col, const CardinalDirection new_door_direction, const bool new_multi_story)
: start_row(new_start_row), end_row(new_end_row), start_col(new_start_col), end_col(new_end_col), door_direction(new_door_direction), multi_story(new_multi_story)
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