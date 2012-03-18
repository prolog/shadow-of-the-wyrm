#include <vector>
#include "WorldGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "CellularAutomataGenerator.hpp"

using namespace std;

WorldGenerator::WorldGenerator()
: Generator("")
{
}

WorldGenerator::WorldGenerator(const string& new_map_exit_id)
: Generator(new_map_exit_id)
{
  // Worlds don't do anything with the map exit id.
}


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
  
  result_map->set_map_type(MAP_TYPE_WORLD);
  result_map->set_map_id("overworld");
  result_map->set_permanent(true);

  return result_map;
}

void WorldGenerator::generate_little_island(MapPtr map)
{
  Dimensions dim = map->size();

  //   ..
  //    ...
  //      .

  int height = dim.get_y();
  int width = dim.get_x();

  // Refill with sea, in case there are land features here already.
  for (int current_height = height - 5; current_height < height; current_height++)
  {
    for (int current_width = width - 6; current_width < width; current_width++)
    {
      TilePtr sea_tile = TileGenerator::generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  // JCD FIXME: Add a keep ruins here.
  TilePtr field_tile = TileGenerator::generate(TILE_TYPE_FIELD);
  map->insert(height-4, width-5, field_tile);

  TilePtr forest_tile = TileGenerator::generate(TILE_TYPE_FOREST);
  map->insert(height-4, width-4, forest_tile);

  // JCD FIXME: Add the village of Isen Dun here.
  forest_tile = TileGenerator::generate(TILE_TYPE_FIELD);
  map->insert(height-3, width-4, forest_tile);

  // Define the starting location:
  Coordinate c;
  c.first  = height - 3;
  c.second = width - 4;
  map->add_or_update_location(WorldMapLocationTextKeys::STARTING_LOCATION, c);

  // JCD FIXME: Add a graveyard here.
  forest_tile = TileGenerator::generate(TILE_TYPE_FIELD);
  map->insert(height-3, width-3, forest_tile);

  field_tile = TileGenerator::generate(TILE_TYPE_FOREST);
  map->insert(height-3, width-2, field_tile);

  // JCD FIXME: Add Crawler's Caves here.
  field_tile = TileGenerator::generate(TILE_TYPE_FIELD);
  map->insert(height-2, width-2, field_tile);
}

// The "last island", where the Big Baddy resides.
void WorldGenerator::generate_far_reaches(MapPtr map)
{
  for (int current_height = 0; current_height < 4; current_height++)
  {
    for (int current_width = 0; current_width < 5; current_width++)
    {
      TilePtr sea_tile = TileGenerator::generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  //    ...
  //   .....
  //   ...

  TilePtr tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(1, 2, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(1, 3, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(1, 4, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(2, 1, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(2, 2, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(2, 3, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(2, 4, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(3, 1, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(3, 2, tile);

  tile = TileGenerator::generate(TILE_TYPE_SCRUB);
  map->insert(3, 3, tile);
}

MapPtr WorldGenerator::generate_set_islands_and_continents(MapPtr map)
{
  generate_little_island(map);
  generate_far_reaches(map);
  return map;
}

// When done, translate the cell map MapPtr.
MapPtr WorldGenerator::generate_random_islands(MapPtr result_map)
{
  TilePtr tile;
  Dimensions dimensions = result_map->size();

  // Field-Islands
  CellularAutomataSettings cas(55, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag(cas, dimensions);
  CellMap cell_map = cag.generate();

  // Forests
  CellularAutomataSettings cas_forest(52, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag_forest(cas_forest, dimensions);
  CellMap forest_cell_map = cag_forest.generate();

  // Mountains
  CellularAutomataSettings cas_mountains(45, 50000, 4, 45, CELL_ON);
  CellularAutomataGenerator cag_mountains(cas_mountains, dimensions);
  CellMap mountains_cell_map = cag_mountains.generate();

  // Scrubland
  CellularAutomataSettings cas_scrub(53, 50000, 4, 53, CELL_OFF);
  CellularAutomataGenerator cag_scrub(cas_scrub, dimensions);
  CellMap scrub_cell_map = cag_scrub.generate();
  
  // Marshes
  CellularAutomataSettings cas_marsh(20, 100, 4, 20, CELL_OFF);
  CellularAutomataGenerator cag_marsh(cas_marsh, dimensions);
  CellMap marsh_cell_map = cag_marsh.generate();
  
  // Desert
  CellularAutomataSettings cas_desert(20, 100, 4, 20, CELL_OFF);
  CellularAutomataGenerator cag_desert(cas_desert, dimensions);
  CellMap desert_cell_map = cag_desert.generate();

  // Now translate the various CellMaps into an overall MapPtr...
  CellValue world_val, forest_val, mountains_val, scrub_val, marsh_val, desert_val;

  int rand = 0;
  int y = dimensions.get_y();
  int x = dimensions.get_x();
  for (int row = 0; row < y; row++)
  {
    for (int col = 0; col < x; col++)
    {
      world_val  = cell_map[row][col];
      forest_val = forest_cell_map[row][col];
      mountains_val = mountains_cell_map[row][col];
      scrub_val = scrub_cell_map[row][col];
      marsh_val = marsh_cell_map[row][col];
      desert_val = desert_cell_map[row][col];

      // Always add fields.  Add forests, scrub, marsh if the tile is not sea.  Add mountains if the tile is field.
      if (world_val == CELL_OFF)
      {
        // 0.5% chance of dungeon
        rand = RNG::range(1, 200);
        if (rand <= 1)
        {
          tile = TileGenerator::generate(TILE_TYPE_DUNGEON_COMPLEX);
        }
        else
        {
          // 1% chance of field village.
          rand = RNG::range(1, 100);
          
          if (rand <= 1)
          {
            tile = TileGenerator::generate(TILE_TYPE_VILLAGE, TILE_TYPE_FIELD);
          }
          else
          {
            tile = TileGenerator::generate(TILE_TYPE_FIELD);
          }            
        }
        
        result_map->insert(row, col, tile);
      }
      
      if (marsh_val == CELL_OFF && world_val == CELL_OFF)
      {
        // 0.5% chance of marsh village
        rand = RNG::range(1, 200);
        
        if (rand <= 1)
        {
          tile = TileGenerator::generate(TILE_TYPE_VILLAGE, TILE_TYPE_MARSH);
        }
        else
        {
          tile = TileGenerator::generate(TILE_TYPE_MARSH);
        }

        result_map->insert(row, col, tile);
      }

      if (forest_val == CELL_OFF && world_val == CELL_OFF)
      {
        // 1% chance of forest village
        rand = RNG::range(1, 100);
        
        if (rand <= 1)
        {
          tile = TileGenerator::generate(TILE_TYPE_VILLAGE, TILE_TYPE_FOREST);
        }
        else
        {
          tile = TileGenerator::generate(TILE_TYPE_FOREST);
        }
        
        result_map->insert(row, col, tile);
      }

      if (scrub_val == CELL_OFF && world_val == CELL_OFF)
      {
        // 0.5% chance of scrub village.
        rand = RNG::range(1, 200);
        
        if (rand <= 1)
        {
          tile = TileGenerator::generate(TILE_TYPE_VILLAGE, TILE_TYPE_SCRUB);
        }
        else
        {
          tile = TileGenerator::generate(TILE_TYPE_SCRUB);          
        }

        result_map->insert(row, col, tile);
      }
      
      // Deserts should only appear in naturally dry areas.
      if (desert_val == CELL_OFF && world_val == CELL_OFF && scrub_val == CELL_OFF)
      {
        tile = TileGenerator::generate(TILE_TYPE_DESERT);
        result_map->insert(row, col, tile);
      }

      if (mountains_val == CELL_OFF && world_val == CELL_OFF && forest_val == CELL_ON)
      {
        // 2% chance of being a dungeon
        // 3% chance of being a cavern
        rand = RNG::range(1, 100);
        
        if (rand <= 2)
        {
          tile = TileGenerator::generate(TILE_TYPE_DUNGEON_COMPLEX);
        }
        else if (rand <= 5)
        {
          tile = TileGenerator::generate(TILE_TYPE_CAVERN);
        }
        else
        {
          tile = TileGenerator::generate(TILE_TYPE_MOUNTAINS);
        }
        
        result_map->insert(row, col, tile);
      }
    }
  }

  return result_map;
}
