#include <vector>
#include "WorldGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "CellularAutomataGenerator.hpp"

using namespace std;

MapPtr WorldGenerator::generate()
{
  // Default is 100x100
  Dimensions default_dimensions(100, 100);
  return generate(default_dimensions);
}

MapPtr WorldGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = MapPtr(new Map(dimensions));

  // Fill the world with water.
  fill(result_map, TILE_TYPE_SEA);

  // Generate the random world
  result_map = generate_random_islands(result_map);

  // Generate set islands/continents.
  result_map = generate_set_islands_and_continents(result_map);

  return result_map;
}

void WorldGenerator::generate_little_island(MapPtr map)
{
  Dimensions dim = map->size();
  TilePtr field_tile = TileGenerator::generate(TILE_TYPE_FIELD);
  TilePtr forest_tile = TileGenerator::generate(TILE_TYPE_FOREST);
  TilePtr sea_tile = TileGenerator::generate(TILE_TYPE_SEA);

  //   ..
  //    ...
  //      .

  int height = dim.get_y();
  int width = dim.get_x();

  // Refill with sea, in case there are land features here already.
  for (int current_height = height - 4; current_height < height; current_height++)
  {
    for (int current_width = width - 6; current_width < width; current_width++)
    {
      map->insert(current_height, current_width, sea_tile);
    }
  }

  map->insert(height-3, width-5, field_tile);
  map->insert(height-3, width-4, forest_tile);
  map->insert(height-2, width-4, forest_tile);

  // Define the starting location:
  Coordinate c;
  c.first  = height - 2;
  c.second = width - 4;
  map->add_location(WorldMapLocationTextKeys::STARTING_LOCATION, c); // JCD FIXME FIXME FIXME

  map->insert(height-2, width-3, forest_tile);
  map->insert(height-2, width-2, field_tile);
  map->insert(height-1, width-2, field_tile);
}

// The "last island", where the Big Baddy resides.
void WorldGenerator::generate_far_reaches(MapPtr map)
{
  Dimensions dim = map->size();
  TilePtr tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  TilePtr sea_tile = TileGenerator::generate(TILE_TYPE_SEA);

  for (int current_height = 0; current_height < 4; current_height++)
  {
    for (int current_width = 0; current_width < 5; current_width++)
    {
      map->insert(current_height, current_width, sea_tile);
    }
  }

  //    ...
  //   .....
  //   ...

  map->insert(1, 2, tile);
  map->insert(1, 3, tile);
  map->insert(1, 4, tile);
  map->insert(2, 1, tile);
  map->insert(2, 2, tile);
  map->insert(2, 3, tile);
  map->insert(2, 4, tile);
  map->insert(3, 1, tile);
  map->insert(3, 2, tile);
  map->insert(3, 3, tile);
}

MapPtr WorldGenerator::generate_set_islands_and_continents(MapPtr map)
{
  generate_little_island(map);
  generate_far_reaches(map);
  return map;
}

// When done, translate the cell map MapPtr.
MapPtr WorldGenerator::generate_random_islands(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));
  TilePtr tile;
  Dimensions dimensions = map->size();

  // Field-Islands
  CellularAutomataSettings cas(55, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag(cas, dimensions);
  CellMap cell_map = cag.generate();

  // Forests
  CellularAutomataSettings cas_forest(52, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag_forest(cas_forest, dimensions);
  CellMap forest_cell_map = cag.generate();

  // Mountains
  CellularAutomataSettings cas_mountains(45, 50000, 4, 45, CELL_ON);
  CellularAutomataGenerator cag_mountains(cas_mountains, dimensions);
  CellMap mountains_cell_map = cag.generate();

  // Scrubland
  CellularAutomataSettings cas_scrub(53, 50000, 4, 53, CELL_OFF);
  CellularAutomataGenerator cag_scrub(cas_scrub, dimensions);
  CellMap scrub_cell_map = cag.generate();

  // Now translate the various CellMaps into an overall MapPtr...
  CellMap::const_iterator world_it, forest_it, mountains_it, scrub_it;
  pair<int, int> coords;

  int y = dimensions.get_y();
  int x = dimensions.get_x();
  for (int row = 0; row < y; row++)
  {
    for (int col = 0; col < x; col++)
    {
      coords = make_pair(row, col);
      world_it  = cell_map.find(coords);
      forest_it = forest_cell_map.find(coords);
      mountains_it = mountains_cell_map.find(coords);
      scrub_it = scrub_cell_map.find(coords);

      // Always add fields.  Add forests if the tile is not sea.  Add mountains if the tile is field.
      if (world_it->second == CELL_OFF)
      {
        tile = TileGenerator::generate(TILE_TYPE_FIELD);
        result_map->insert(row, col, tile);
      }

      if (forest_it->second == CELL_OFF && world_it->second == CELL_OFF)
      {
        tile = TileGenerator::generate(TILE_TYPE_FOREST);
        result_map->insert(row, col, tile);
      }

      if (scrub_it->second == CELL_OFF && world_it->second == CELL_OFF)
      {
        tile = TileGenerator::generate(TILE_TYPE_SCRUB);
        result_map->insert(row, col, tile);
      }

      if (mountains_it->second == CELL_OFF && world_it->second == CELL_OFF && forest_it->second == CELL_ON)
      {
        tile = TileGenerator::generate(TILE_TYPE_MOUNTAINS);
        result_map->insert(row, col, tile);
      }
    }
  }

  return result_map;
}
