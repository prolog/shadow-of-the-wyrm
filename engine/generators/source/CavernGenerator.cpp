#include <set>
#include "CavernGenerator.hpp"
#include "CellularAutomataGenerator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "MapExitUtils.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;

int CavernGenerator::MIN_NUM_TRAPS = 0;
int CavernGenerator::MAX_NUM_TRAPS = 6;

CavernGenerator::CavernGenerator(const string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_CAVERN)
{
}

// Generate a cellular automata based cavern, connecting the individual components in a second pass afterwards.
// JCD FIXME refactor as necessary
MapPtr CavernGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_ROCK);

  generate_cavern(result_map);
  reset_cavern_edges(result_map);
  MapComponents cc = get_cavern_components(result_map);
  connect_cavern_components(result_map, cc);
  generate_traps(result_map);

  update_depth_details(result_map);
  generate_staircases(result_map);
  
  result_map->set_map_type(MapType::MAP_TYPE_UNDERWORLD);
  
  return result_map;
}

void CavernGenerator::generate_cavern(MapPtr map)
{
  TileGenerator tg;
  TilePtr tile;
  Dimensions dimensions = map->size();

  int num_iterations = RNG::range(1000, 5000);

  CellularAutomataSettings cas(70, num_iterations, 4, 70, CellValue::CELL_OFF);
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

      if (cavern_val == CellValue::CELL_OFF)
      {
        tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
        map->insert(row, col, tile);
      }
    }
  }
}

MapComponents CavernGenerator::get_cavern_components(MapPtr map)
{
  MapComponents result;
  set<TileType> exclusion_tiles;

  exclusion_tiles.insert(TileType::TILE_TYPE_ROCK);
  result = MapUtils::get_map_components(map, exclusion_tiles);

  return result;
}

// Dig a line between two points
void CavernGenerator::connect_caverns(MapPtr map, const Coordinate& start, const Coordinate& end)
{
  TileGenerator tg;

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
    TilePtr tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
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
  TileGenerator tg;

  Dimensions dimensions = map->size();
  int max_rows = dimensions.get_y();
  int max_cols = dimensions.get_x();

  for (int row = 0; row < max_rows; row++)
  {
    TilePtr rock = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(row, 0, rock);
    
    rock = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(row, max_cols-1, rock);
  }

  for (int col = 0; col < max_cols; col++)
  {
    TilePtr rock = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(0, col, rock);
    
    rock = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(max_rows-1, col, rock);
  }
}

// Generate both staircases, if necessary.  It may not be necessary
// to generate the down staircase.
void CavernGenerator::generate_staircases(MapPtr map)
{
  // Up Staircase
  generate_staircase(map, TileType::TILE_TYPE_UP_STAIRCASE, Direction::DIRECTION_UP);
    
  // Down staircase
  Depth depth = map->size().depth();

  if (depth.get_current() < depth.get_maximum())
  {
    generate_staircase(map, TileType::TILE_TYPE_DOWN_STAIRCASE, Direction::DIRECTION_DOWN);
  }
}

// Generate a particular staircase
void CavernGenerator::generate_staircase(MapPtr map, const TileType tile_type, const Direction direction)
{
  TileGenerator tg;
  Dimensions dimensions = map->size();

  bool found = false;
  Coordinate c;
  int max_y = dimensions.get_y();
  int max_x = dimensions.get_x();
  
  while (!found)
  {
    c.first  = RNG::range(0, max_y-1);
    c.second = RNG::range(0, max_x-1);
    
    // Check the tile to see if it's floor
    TilePtr tile = map->at(c);
    
    if (!tile) break;
    if (tile && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
    {
      if (tile_type == TileType::TILE_TYPE_UP_STAIRCASE)
      {
        place_up_staircase(map, c.first, c.second, TileType::TILE_TYPE_CAVERN, direction, get_permanence_default(), true);
      }
      else
      {
        place_down_staircase(map, c.first, c.second, TileType::TILE_TYPE_CAVERN, direction, get_permanence_default(), true);
      }
      break;
    }
  }
}

// Goblins and other tricksy things that live underground can set traps 
// almost anywhere.  Instead of generating them in rooms, like dungeons,
// generate them in any accessible tile.
void CavernGenerator::generate_traps(MapPtr map)
{
  int num_traps = RNG::range(MIN_NUM_TRAPS, MAX_NUM_TRAPS);
  GeneratorUtils::generate_traps(map, num_traps);
}

MapType CavernGenerator::get_map_type() const
{
  return MapType::MAP_TYPE_UNDERWORLD;
}

bool CavernGenerator::get_permanence_default() const
{
  return true;
}

bool CavernGenerator::can_create_initial_items() const
{
  return true;
}