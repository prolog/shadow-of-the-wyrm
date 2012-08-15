#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "SettlementGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;
using boost::make_shared;

SettlementGenerator::SettlementGenerator(MapPtr new_base_map)
: BaseSettlementGenerator(new_base_map)
{
}

SettlementGenerator::SettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: BaseSettlementGenerator(new_base_map, new_growth_rate)
{
}

MapPtr SettlementGenerator::generate(const Dimensions& dimensions)
{
  return generate();
}

MapPtr SettlementGenerator::generate()
{
  MapPtr result_map = make_shared<Map>(*base_map);

  result_map = generate_roads_and_buildings(result_map);
  result_map = populate_settlement(result_map);

  return result_map;
}

MapPtr SettlementGenerator::generate_roads_and_buildings(MapPtr map)
{
  MapPtr result_map = make_shared<Map>(*map);

  int settlement_type = RNG::range(1, 2);

  switch(settlement_type)
  {
    case 1:
    case 2:
      result_map = generate_settlement_with_square_and_cardinal_roads(result_map);
      break;
    default:
      break;
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_square(MapPtr map, const int start_row, const int start_col, const int square_size)
{
  MapPtr result_map = make_shared<Map>(*map);

  int road_top    = start_row - 1;
  int road_bottom = start_row+square_size+1;
  int road_left   = start_col-1;
  int road_right  = start_col+square_size+1;

  for (int current_row = road_top; current_row <= road_bottom; current_row++)
  {
    for (int current_col = road_left; current_col <= road_right; current_col++)
    {
      int rand = RNG::range(1, 100);

      if (rand <= growth_rate)
      {
        if ((current_row == road_top) || (current_row == road_bottom) || (current_col == road_left) || (current_col == road_right))
        {
          TilePtr road_tile = TileGenerator::generate(TILE_TYPE_ROAD);
          result_map->insert(current_row, current_col, road_tile);
        }
        else
        {
          TilePtr square_tile;

          if ((current_col + current_row) % 2 == 0)
          {
            square_tile = TileGenerator::generate(TILE_TYPE_FIELD);
          }
          else
          {
            square_tile = TileGenerator::generate(TILE_TYPE_TREE);
          }

          result_map->insert(current_row, current_col, square_tile);
        }
      }
    }
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_settlement_with_square_and_cardinal_roads(MapPtr map)
{
  MapPtr result_map = make_shared<Map>(*map);
  Dimensions dim    = result_map->size();
  int num_rows      = dim.get_y();
  int num_cols      = dim.get_x();

  // Generate the central square.
  int square_size = RNG::range(2, 4);
  int start_row   = (num_rows / 2) - (square_size / 2);
  int start_col   = (num_cols / 2) - (square_size / 2);

  result_map = generate_square(result_map, start_row, start_col, square_size);

  // Generate the roads leading out, filling them with buildings.
  // JCD FIXME: Refactor, seriously.  This is ugly.
  generate_road_north(result_map, start_row-2, (start_col+(square_size/2)), start_row-2, 100);
  generate_road_south(result_map, (start_row+square_size+2), (start_col+(square_size/2)), num_rows-start_row+square_size+2, 100);
  generate_road_east(result_map, (start_row+(square_size/2)), (start_col+square_size+2), num_cols-start_col+square_size+2, 100);
  generate_road_west(result_map, (start_row+(square_size/2)), (start_col-2), start_col-2, 100);

  return result_map;
}

MapPtr SettlementGenerator::generate_settlement_with_winding_road(MapPtr map)
{
  // JCD FIXME: Implement this.
  return map;
}

MapPtr SettlementGenerator::populate_settlement(MapPtr map)
{
  MapPtr result_map = make_shared<Map>(*map);

  return result_map;
}
