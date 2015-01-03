#pragma once
#include "Map.hpp"

// Populates a treasure room, given a map, a particular range of tiles,
// and a danger level.
class TreasureRoomPopulator
{
  public:
    void populate_treasure_room(MapPtr map, const TileType tile_type, const int danger_level, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall);

  protected:
    void generate_corner_features(MapPtr map, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall);
    void generate_creatures(MapPtr map, const TileType tile_type, const int danger_level, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall);
    void generate_treasure(MapPtr map, const int danger_level, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall);
};

