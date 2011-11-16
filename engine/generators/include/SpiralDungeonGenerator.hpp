#pragma once
#include "DungeonGenerator.hpp"
#include "StaircaseTile.hpp"
#include "Directions.hpp"

class SpiralDungeonGenerator : public DungeonGenerator
{
  public:
    SpiralDungeonGenerator();
    virtual MapPtr generate(const Dimensions& dimensions);

  protected:
    MapPtr generate_spiral_dungeon(MapPtr map);
    void   generate_spiral(MapPtr map, const int current_row, const int current_col, const CardinalDirection direction, const int row_length, const int col_length);
    MapPtr place_staircases(MapPtr map, const bool place_up_staircase = true, const bool place_down_staircase = true);
    MapPtr place_random_staircase(MapPtr, StaircaseTilePtr staircase_tile);

    const int SPACE_BETWEEN_SPIRALS;
};
