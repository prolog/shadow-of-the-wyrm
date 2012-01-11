#include "CavernGenerator.hpp"
#include "CellularAutomataGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include <iostream>
#include <set>
using namespace std;

// Generate a cellular automata based cavern, connecting the individual components in a second pass afterwards.
// JCD FIXME refactor as necessary
MapPtr CavernGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_ROCK);

  generate_cavern(result_map);
  reset_cavern_edges(result_map);
  MapComponents cc = get_cavern_components(result_map);
  connect_cavern_components(result_map, cc);
  
  result_map->set_map_type(MAP_TYPE_UNDERWORLD);
  
  return result_map;
}

void CavernGenerator::generate_cavern(MapPtr map)
{
  TilePtr tile;
  Dimensions dimensions = map->size();

  int num_iterations = RNG::range(1000, 7500);

  CellularAutomataSettings cas(70, num_iterations, 4, 70, CELL_OFF);
  CellularAutomataGenerator cag(cas, dimensions);
  CellMap cavern_map = cag.generate();

  CellValue cavern_val;

  int y = dimensions.get_y();
  int x = dimensions.get_x();
  for (int row = 0; row < y; row++)
  {
    for (int col = 0; col < x; col++)
    {
      cavern_val = cavern_map[row][col];

      if (cavern_val == CELL_OFF)
      {
        tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
        map->insert(row, col, tile);
      }
    }
  }
}

MapComponents CavernGenerator::get_cavern_components(MapPtr map)
{
  MapComponents result;
  set<TileType> exclusion_tiles;

  exclusion_tiles.insert(TILE_TYPE_ROCK);
  result = MapUtils::get_map_components(map, exclusion_tiles);

  return result;
}

// Dig a line between two points
void CavernGenerator::connect_caverns(MapPtr map, const Coordinate& start, const Coordinate& end)
{
  int current_y = start.first;
  int current_x = start.second;
  int end_y     = end.first;
  int end_x     = end.second;
  int inc_y     = 1;
  int inc_x     = 1;

  if (current_y > end_y)
  {
    inc_y *= -1;
  }

  if (current_x > end_x)
  {
    inc_x *= -1;
  }

  while (current_y != end_y || current_x != end_x)
  {
    TilePtr tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
    map->insert(current_y, current_x, tile);

    if (current_y != end_y)
    {
      current_y += inc_y;
    }

    if (current_x != end_x)
    {
      current_x += inc_x;
    }
  }
}

// Connect a list of cavern components.  For each component, create a path from it to the next one in the list.
void CavernGenerator::connect_cavern_components(MapPtr map, const MapComponents& cc)
{
  int number_of_components = cc.size();

  if (number_of_components > 1)
  {
    for (int current_component = 0; current_component < number_of_components-1; current_component++)
    {
      Component first_component = cc.at(current_component);
      Component next_component  = cc.at(current_component+1);

      int rand_first = RNG::range(0, first_component.size()-1);
      int rand_second = RNG::range(0, next_component.size()-1);

      int first_ix = 0;
      ComponentItc c_it = first_component.begin();
      while (first_ix < rand_first)
      {
        c_it++;
        first_ix++;
      }

      Coordinate first_coord = *c_it;

      int second_ix = 0;
      c_it = next_component.begin();
      while (second_ix < rand_second)
      {
        c_it++;
        second_ix++;
      }

      Coordinate second_coord = *c_it;

      connect_caverns(map, first_coord, second_coord);
    }
  }
}

void CavernGenerator::reset_cavern_edges(MapPtr map)
{
  Dimensions dimensions = map->size();
  int max_rows = dimensions.get_y();
  int max_cols = dimensions.get_x();
  TilePtr rock = TileGenerator::generate(TILE_TYPE_ROCK);

  for (int row = 0; row < max_rows; row++)
  {
    map->insert(row, 0, rock);
    map->insert(row, max_cols-1, rock);
  }

  for (int col = 0; col < max_cols; col++)
  {
    map->insert(0, col, rock);
    map->insert(max_rows-1, col, rock);
  }
}
