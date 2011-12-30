#include "Log.hpp"
#include "RoadGenerator.hpp"
#include "TileGenerator.hpp"

RoadGenerator::RoadGenerator(const int width)
: ROAD_WIDTH(width)
, ROAD_DIRECTION( CARDINAL_DIRECTION_SOUTH )
{
}

RoadGenerator::RoadGenerator(const CardinalDirection direction, const int width)
: ROAD_WIDTH(width)
, ROAD_DIRECTION(direction)
{
}

void RoadGenerator::generate_road(MapPtr map)
{
  TilePtr tile;
  Dimensions d = map->size();
  int max_rows = d.get_y();
  int max_cols = d.get_x();
  int col_start, col_end, row_start, row_end;

  switch( ROAD_DIRECTION )
  {
    case CARDINAL_DIRECTION_NORTH:
    case CARDINAL_DIRECTION_SOUTH:
      col_start = ((max_cols / 2) - (ROAD_WIDTH / 2));
      col_end = col_start + ROAD_WIDTH;
      for (int current_col = col_start; current_col < col_end; current_col++)
      {
        for (int current_row = 0; current_row < max_rows; current_row++)
        {
          tile = TileGenerator::generate(TILE_TYPE_ROAD);
          map->insert(current_row, current_col, tile);
        }
      }
      break;
    case CARDINAL_DIRECTION_EAST:
    case CARDINAL_DIRECTION_WEST:
      row_start = ((max_rows / 2) - (ROAD_WIDTH / 2));
      row_end = row_start + ROAD_WIDTH;
      for (int current_row = row_start; current_row < row_end; current_row++)
      {
        for (int current_col = 0; current_col < max_cols; current_col++)
        {
          tile = TileGenerator::generate(TILE_TYPE_ROAD);
          map->insert(current_row, current_col, tile);
        }
      }
      break;
    default:
      Log::instance()->log("Unhandled direction in road generation");
      break;
  }
}

MapPtr RoadGenerator::generate(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));

  generate_road(result_map);

  return result_map;
}
