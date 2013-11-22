#include <vector>
#include <boost/make_shared.hpp>
#include "AlignmentEnums.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "DungeonGenerator.hpp"
#include "Game.hpp"
#include "WorldGenerator.hpp"
#include "TileGenerator.hpp"
#include "TileIDs.hpp"
#include "RNG.hpp"
#include "CellularAutomataGenerator.hpp"
#include "MapProperties.hpp"
#include "Serialize.hpp"
#include "TileExtraDescriptionKeys.hpp"
#include "VillageTile.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

// Even though the map_terrain_type parameter is used to generate creatures, and UNDEFINED would normally be bad, it
// shouldn't matter for the world, since there will never be creatures generated on it.
//
// The tile generator should not generate any random items on the world map!
// Those items cannot be picked up.
WorldGenerator::WorldGenerator()
: Generator("", TILE_TYPE_UNDEFINED), tg(false)
{
}

WorldGenerator::WorldGenerator(const string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_UNDEFINED)
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
  // Clear the state variables, in case this generator has already had a run.
  village_coordinates.clear();
  unused_initial_race_ids.clear();
  
  MapPtr result_map = boost::make_shared<Map>(dimensions);

  // Fill the world with water.
  fill(result_map, TILE_TYPE_SEA);

  // Generate the random world
  result_map = generate_random_islands(result_map);

  // Generate set islands/continents.
  result_map = generate_set_islands_and_continents(result_map);
  
  // Generate villages and their surroundings
  populate_race_information();
  set_village_races(result_map);
  generate_village_surroundings(result_map);  
  
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
      TilePtr sea_tile = tg.generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  // Wintersea Keep
  TilePtr wintersea_keep = tg.generate(TILE_TYPE_KEEP, TILE_TYPE_UNDEFINED);
  wintersea_keep->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_WINTERSEA_KEEP);
  wintersea_keep->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_WINTERSEA_KEEP);
  map->insert(height-4, width-5, wintersea_keep);

  TilePtr forest_tile = tg.generate(TILE_TYPE_FOREST);
  map->insert(height-4, width-4, forest_tile);

  // Village of Isen Dun.
  TilePtr isen_dun = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_FIELD);
  isen_dun->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_ISEN_DUN);
  isen_dun->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_ISEN_DUN);
  map->insert(height-3, width-4, isen_dun);

  // Define the starting location:
  Coordinate c;
  c.first  = height - 4;
  c.second = width - 4;
  map->add_or_update_location(WorldMapLocationTextKeys::STARTING_LOCATION, c);

  // The Barrows
  TilePtr isen_dun_graveyard = tg.generate(TILE_TYPE_GRAVEYARD, TILE_TYPE_UNDEFINED);
  isen_dun_graveyard->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_ISEN_DUN_GRAVEYARD);
  isen_dun_graveyard->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_THE_BARROWS);
  map->insert(height-3, width-3, isen_dun_graveyard);

  TilePtr wild_orchard_tile = tg.generate(TILE_TYPE_WILD_ORCHARD);
  map->insert(height-3, width-2, wild_orchard_tile);

  // Siriath's Dungeons
  TilePtr village_dungeon = tg.generate(TILE_TYPE_DUNGEON_COMPLEX, TILE_TYPE_UNDEFINED);
  village_dungeon->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_ISEN_DUN_DUNGEON);
  // Sirith's dungeon is eight levels deep.
  village_dungeon->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH, Integer::to_string(8));
  map->insert(height-2, width-2, village_dungeon);
}

// Last Rock: a tiny island where an old exile lives.
// Far Shore: an even smaller island where his sister used to live.
void WorldGenerator::generate_last_rock_and_far_shore(MapPtr map)
{
  Dimensions dim = map->size();
  int height = dim.get_y();
  int width = dim.get_x();

  // Refill last rock area with sea, in case there are land features 
  // here already.
  for (int current_height = height - 16; current_height < height-14; current_height++)
  {
    for (int current_width = width - 5; current_width < width; current_width++)
    {
      TilePtr sea_tile = tg.generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  TilePtr last_rock = tg.generate(TILE_TYPE_ROCKY_EARTH);
  last_rock->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_LAST_ROCK);
  last_rock->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_LAST_ROCK);
  map->insert(height-15, width-1, last_rock);

  // Refill far shore area with sea, in case there are land features 
  // here already.
  for (int current_height = height - 11; current_height < height-9; current_height++)
  {
    for (int current_width = 0; current_width < 4; current_width++)
    {
      TilePtr sea_tile = tg.generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  TilePtr far_shore = tg.generate(TILE_TYPE_FOREST);
  far_shore->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_FAR_SHORE);
  far_shore->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_FAR_SHORE);
  map->insert(height-10, 0, far_shore);
}

// The island containing the only infinite, Angband-style dungeon in the game.
void WorldGenerator::generate_infinite_dungeon_island(MapPtr map)
{
  // Surround the island with sea
  Dimensions dim = map->size();
  int height = dim.get_y();
  int width = dim.get_x();

  // Refill with sea, in case there are land features here already.
  for (int current_height = height - 12; current_height < height-9; current_height++)
  {
    for (int current_width = width - 7; current_width < width; current_width++)
    {
      TilePtr sea_tile = tg.generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  // Create the island itself:
  //
  //  ~T~
  //  T<T
  //  ~T~
  //
  // First, the surrounding forest:
  vector<Coordinate> v_trees;
  v_trees.push_back(make_pair(height-11, width-2));
  v_trees.push_back(make_pair(height-10, width-1));
  v_trees.push_back(make_pair(height-10, width-3));
  v_trees.push_back(make_pair(height-9, width-2));

  for (const Coordinate& coord : v_trees)
  {
    TilePtr forest_tile = tg.generate(TILE_TYPE_FOREST);
    map->insert(coord.first, coord.second, forest_tile);
  }

  // Next, the actual dungeon, setting the "impermanance" flag:
  TilePtr inf_dungeon_tile = tg.generate(TILE_TYPE_DUNGEON_COMPLEX);
  inf_dungeon_tile->set_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE, Bool::to_string(false));
  inf_dungeon_tile->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH, Integer::to_string(numeric_limits<int>::max()));
  inf_dungeon_tile->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_INFINITE_DUNGEON);
  map->insert(height-10, width-2, inf_dungeon_tile);
}

// The "last island", where Amaurosis resides.
void WorldGenerator::generate_far_reaches(MapPtr map)
{
  for (int current_height = 0; current_height < 4; current_height++)
  {
    for (int current_width = 0; current_width < 5; current_width++)
    {
      TilePtr sea_tile = tg.generate(TILE_TYPE_SEA);
      map->insert(current_height, current_width, sea_tile);
    }
  }

  //    ...
  //   .....
  //   ...

  TilePtr tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(1, 2, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(1, 3, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(1, 4, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(2, 1, tile);

  // Amaurosis' lair.
  TilePtr lair_tile = tg.generate(TILE_TYPE_CAVERN);
  lair_tile->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_LAST_ISLAND_LAIR);
  lair_tile->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_LAST_ISLAND_LAIR);
  map->insert(2, 2, lair_tile);
  
  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(2, 3, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(2, 4, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(3, 1, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(3, 2, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(3, 3, tile);
}

void WorldGenerator::generate_fixed_settlements(MapPtr map)
{
  generate_Gnordvar(map);
  generate_Forest_of_Yew(map);
}

void WorldGenerator::generate_Gnordvar(MapPtr map)
{
  //  .
  // ..
  // ..
  // .
  Dimensions dim = map->size();
  int height = dim.get_y();
  int width = dim.get_x();

  TilePtr tile = tg.generate(TILE_TYPE_FIELD);
  map->insert(height-58, width-6, tile);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(height-57, width-7, tile);

  TilePtr gnordvar = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_FIELD);
  gnordvar->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_GNORDVAR);
  gnordvar->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_GNORDVAR);
  map->insert(height-57, width-6, gnordvar);

  string l20 = Integer::to_string(20);
  TilePtr gnordvar_mines = tg.generate(TILE_TYPE_MINE);
  gnordvar_mines->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_GNORDVAR_MINES);
  gnordvar_mines->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_DEPTH, l20);
  gnordvar_mines->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH, l20);

  // Set up creatures for mines.
  vector<string> creatures_to_generate;
  creatures_to_generate.push_back("black_manticore");

  int num_satyrs = RNG::range(5, 10);
  for (int i = 0; i < num_satyrs; i++)
  {
    creatures_to_generate.push_back("satyr");
  }

  string creature_str = String::create_csv_from_string_vector(creatures_to_generate);
  gnordvar_mines->set_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES, creature_str);

  map->insert(height-56, width-7, gnordvar_mines);

  tile = tg.generate(TILE_TYPE_MOUNTAINS);
  map->insert(height-56, width-6, tile);

  tile = tg.generate(TILE_TYPE_FIELD);
  map->insert(height-55, width-7, tile);
}

void WorldGenerator::generate_Lalos_Grotto(MapPtr map)
{
  Dimensions dim = map->size();
  int height = dim.get_y();
  int width = dim.get_x();

  TileGenerator tg;

  TilePtr lalos_grotto_tile = tg.generate(TILE_TYPE_CAVERN);
  string l14 = Integer::to_string(14);
  lalos_grotto_tile->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_LALOS_GROTTO);
  lalos_grotto_tile->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_DEPTH, l14);
  lalos_grotto_tile->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH, l14);

  vector<string> creature_types;
  creature_types.push_back("skeleton");
  creature_types.push_back("thrall");
  creature_types.push_back("ghoul");
  creature_types.push_back("grey_glider");
  creature_types.push_back("lichling");
  creature_types.push_back("corpse_bird");
  creature_types.push_back("quisling");

  vector<string> creatures_to_generate;

  for (const string& creature : creature_types)
  {
    int num_creature = RNG::range(9, 13);

    for (int i = 0; i < num_creature; i++)
    {
      creatures_to_generate.push_back(creature);
    }
  }

  creatures_to_generate.push_back("lalo");

  string creature_str = String::create_csv_from_string_vector(creatures_to_generate);
  lalos_grotto_tile->set_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES, creature_str);

  map->insert(height-39, width-20, lalos_grotto_tile);
}

void WorldGenerator::generate_Forest_of_Yew(MapPtr map)
{
  // o %
  // %%%
  //  %
  TileGenerator tg;

  Dimensions dim = map->size();
  int height = dim.get_y();
  int width = dim.get_x();

  TilePtr sea_tile;

  // Make the elfy little island by ensuring there's enough sea.
  for (int row = height - 40; row < height - 36; row++)
  {
    for (int col = width - 21; col < width - 16; col++)
    {
      sea_tile = tg.generate(TILE_TYPE_SEA);
      map->insert(row, col, sea_tile);
    }
  }

  generate_Lalos_Grotto(map);

  TilePtr forest_tile = tg.generate(TILE_TYPE_FOREST);
  map->insert(height-39, width-18, forest_tile);

  forest_tile = tg.generate(TILE_TYPE_FOREST);
  map->insert(height-38, width-20, forest_tile);
  TilePtr forest_of_yew = tg.generate(TILE_TYPE_FOREST);
  forest_of_yew->set_extra_description_sid(TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_FOREST_OF_YEW);
  forest_of_yew->set_custom_map_id(TileCustomMapIDs::CUSTOM_MAP_ID_FOREST_OF_YEW);
  map->insert(height-38, width-19, forest_of_yew);
  forest_tile = tg.generate(TILE_TYPE_FOREST);
  map->insert(height-38, width-18, forest_tile);

  forest_tile = tg.generate(TILE_TYPE_FOREST);
  map->insert(height-37, width-19, forest_tile);
}

MapPtr WorldGenerator::generate_set_islands_and_continents(MapPtr map)
{
  generate_little_island(map);
  generate_infinite_dungeon_island(map);
  generate_far_reaches(map);
  generate_last_rock_and_far_shore(map);
  generate_fixed_settlements(map);

  return map;
}

// When done, translate the cell map MapPtr.
MapPtr WorldGenerator::generate_random_islands(MapPtr result_map)
{
  TilePtr tile;
  Dimensions dimensions = result_map->size();
  int rows = dimensions.get_y();
  int cols = dimensions.get_x();
  
  CellMap cell_map, forest_cell_map, hills_cell_map, mountains_cell_map, scrub_cell_map, marsh_cell_map, desert_cell_map;
  CellValue world_val, forest_val, hills_val, mountains_val, scrub_val, marsh_val, desert_val;
  
  populate_terrain_cell_maps(dimensions, cell_map, forest_cell_map, hills_cell_map, mountains_cell_map, scrub_cell_map, marsh_cell_map, desert_cell_map);

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      world_val  = cell_map[row][col];
      forest_val = forest_cell_map[row][col];
      hills_val = hills_cell_map[row][col];
      mountains_val = mountains_cell_map[row][col];
      scrub_val = scrub_cell_map[row][col];
      marsh_val = marsh_cell_map[row][col];
      desert_val = desert_cell_map[row][col];

      // Always add field, if available.  Add forests, scrub, marsh if the tile is not sea.  Add mountains if the tile is field.
      process_field_cell(result_map, row, col, world_val);
      process_hill_cell(result_map, row, col, hills_val, world_val);
      process_marsh_cell(result_map, row, col, marsh_val, world_val);
      process_forest_cell(result_map, row, col, forest_val, world_val);
      process_scrub_cell(result_map, row, col, scrub_val, world_val);
      process_desert_cell(result_map, row, col, desert_val, scrub_val, world_val);
      process_mountain_cell(result_map, row, col, mountains_val, forest_val, world_val);
    }
  }

  return result_map;
}

// Populate the various cell maps by running cellular automata simulations and assigning the values to the maps.
void WorldGenerator::populate_terrain_cell_maps
(
  const Dimensions& dimensions
, CellMap& field_cell_map
, CellMap& forest_cell_map
, CellMap& hills_cell_map
, CellMap& mountains_cell_map
, CellMap& marsh_cell_map
, CellMap& scrub_cell_map
, CellMap& desert_cell_map
)
{
  // Field-Islands
  CellularAutomataSettings cas(55, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag(cas, dimensions);
  field_cell_map = cag.generate();

  // Forests
  CellularAutomataSettings cas_forest(52, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag_forest(cas_forest, dimensions);
  forest_cell_map = cag_forest.generate();
  
  // Hills
  CellularAutomataSettings cas_hills(51, 50000, 4, 54, CELL_OFF);
  CellularAutomataGenerator cag_hills(cas_hills, dimensions);
  hills_cell_map = cag_hills.generate();

  // Mountains
  CellularAutomataSettings cas_mountains(45, 50000, 4, 45, CELL_ON);
  CellularAutomataGenerator cag_mountains(cas_mountains, dimensions);
  mountains_cell_map = cag_mountains.generate();

  // Scrubland
  CellularAutomataSettings cas_scrub(53, 50000, 4, 53, CELL_OFF);
  CellularAutomataGenerator cag_scrub(cas_scrub, dimensions);
  scrub_cell_map = cag_scrub.generate();
  
  // Marshes
  CellularAutomataSettings cas_marsh(20, 100, 4, 20, CELL_OFF);
  CellularAutomataGenerator cag_marsh(cas_marsh, dimensions);
  marsh_cell_map = cag_marsh.generate();
  
  // Desert
  CellularAutomataSettings cas_desert(20, 100, 4, 20, CELL_OFF);
  CellularAutomataGenerator cag_desert(cas_desert, dimensions);
  desert_cell_map = cag_desert.generate();
}

// Handle generation of field terrain
void WorldGenerator::process_field_cell(MapPtr result_map, const int row, const int col, const CellValue world_val)
{
  TilePtr tile;
  int rand;
  
  // Always add fields.  
  if (world_val == CELL_OFF)
  {
    // 0.5% chance of dungeon
    rand = RNG::range(1, 200);
    if (rand <= 1)
    {
      tile = tg.generate(TILE_TYPE_DUNGEON_COMPLEX);
    }
    else
    {
      // 1% chance of field village.
      rand = RNG::range(1, 100);
      Coordinate c(row, col);

      if (rand <= 1)
      {
        tile = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_FIELD);
        village_coordinates.insert(c);
      }
      else
      {
        remove_village_coordinates_if_present(c);
        tile = tg.generate(TILE_TYPE_FIELD, TILE_TYPE_UNDEFINED);
      }            
    }
    
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_hill_cell(MapPtr result_map, const int row, const int col, const CellValue hills_val, const CellValue world_val)
{
  if (hills_val == CELL_OFF && world_val == CELL_OFF)
  {
    TilePtr tile;
    int rand;
    
    // 1% chance of a hills village
    rand = RNG::range(1, 100);
    Coordinate c(row, col);
    
    if (rand <= 1)
    {
      tile = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_HILLS);
      village_coordinates.insert(c);
    }
    else
    {
      remove_village_coordinates_if_present(c);
      tile = tg.generate(TILE_TYPE_HILLS);      
    }
    
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_marsh_cell(MapPtr result_map, const int row, const int col, const CellValue marsh_val, const CellValue world_val)
{
  TilePtr tile;
  int rand;
  
  if (marsh_val == CELL_OFF && world_val == CELL_OFF)
  {
    // 0.5% chance of marsh village
    rand = RNG::range(1, 200);
    Coordinate c(row, col);
    
    if (rand <= 1)
    {
      tile = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_MARSH);
      village_coordinates.insert(c);
    }
    else
    {
      remove_village_coordinates_if_present(c);
      tile = tg.generate(TILE_TYPE_MARSH);
    }

    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_forest_cell(MapPtr result_map, const int row, const int col, const CellValue forest_val, const CellValue world_val)
{
  TilePtr tile;
  int rand;
  
  if (forest_val == CELL_OFF && world_val == CELL_OFF)
  {
    // 1% chance of forest village, and 1% chance of a wild orchard.
    rand = RNG::range(1, 100);
    Coordinate c(row, col);

    if (rand <= 1)
    {
      tile = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_FOREST);      
      village_coordinates.insert(c);
    }
    else if (rand <= 2)
    {
      remove_village_coordinates_if_present(c);
      tile = tg.generate(TILE_TYPE_WILD_ORCHARD);
    }
    else
    {
      remove_village_coordinates_if_present(c);
      tile = tg.generate(TILE_TYPE_FOREST);
    }
    
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_scrub_cell(MapPtr result_map, const int row, const int col, const CellValue scrub_val, const CellValue world_val)
{
  TilePtr tile;
  int rand;
  
  if (scrub_val == CELL_OFF && world_val == CELL_OFF)
  {
    // 0.5% chance of scrub village.
    rand = RNG::range(1, 200);
    Coordinate c(row, col);
    
    if (rand <= 1)
    {
      tile = tg.generate(TILE_TYPE_VILLAGE, TILE_TYPE_SCRUB);
      village_coordinates.insert(c);
    }
    else
    {
      remove_village_coordinates_if_present(c);
      tile = tg.generate(TILE_TYPE_SCRUB);          
    }

    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_desert_cell(MapPtr result_map, const int row, const int col, const CellValue desert_val, const CellValue scrub_val, const CellValue world_val)
{
  TilePtr tile;
  
  // Deserts should only appear in naturally dry areas.
  if (desert_val == CELL_OFF && world_val == CELL_OFF && scrub_val == CELL_OFF)
  {
    tile = tg.generate(TILE_TYPE_DESERT);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_mountain_cell(MapPtr result_map, const int row, const int col, const CellValue mountains_val, const CellValue forest_val, const CellValue world_val)
{
  TilePtr tile;
  int rand;

  if (mountains_val == CELL_OFF && world_val == CELL_OFF && forest_val == CELL_ON)
  {
    // 2% chance of being a dungeon
    // 3% chance of being a cavern
    rand = RNG::range(1, 100);
    Coordinate c(row, col);
    
    if (rand <= 2)
    {
      tile = tg.generate(TILE_TYPE_DUNGEON_COMPLEX);
    }
    else if (rand <= 5)
    {
      tile = tg.generate(TILE_TYPE_CAVERN);
    }
    else
    {
      tile = tg.generate(TILE_TYPE_MOUNTAINS);
    }
    
    remove_village_coordinates_if_present(c);
    result_map->insert(row, col, tile);
  }
}

// Get the IDs of all user-playable races, and populate them into the list
// of initial race IDs.
void WorldGenerator::populate_race_information()
{
  Game& game = Game::instance();
  
  RaceMap races = game.get_races_ref();
    
  for (RaceMap::const_iterator r_it = races.begin(); r_it != races.end(); r_it++)
  {
    string current_race_id = r_it->first;
    RacePtr race = r_it->second;
      
    if (race && race->get_user_playable())
    {
      unused_initial_race_ids.insert(current_race_id);
    }
  }
}

// JCD FIXME: Unwieldy, refactor.
void WorldGenerator::set_village_races(MapPtr map)
{
// Sometimes useful to know:
//  int total_villages = village_coordinates.size();

  Game& game = Game::instance();
  
  RaceMap races = game.get_races_ref();

  for (const Coordinate& c : village_coordinates)
  {
    TilePtr tile = map->at(c.first, c.second);
    VillageTilePtr village_tile = dynamic_pointer_cast<VillageTile>(tile);
      
    if (village_tile)
    {
      if (!unused_initial_race_ids.empty())
      {
        int rand_race_id_idx = RNG::range(0, unused_initial_race_ids.size()-1);
        set<string>::iterator race_id_it;
          
        int count = 0;
        for (race_id_it = unused_initial_race_ids.begin(); race_id_it != unused_initial_race_ids.end(); race_id_it++)
        {
          if (count == rand_race_id_idx)
          {
            string race_id = *race_id_it;
            RacePtr race = races[race_id];
              
            // Only populate user-playable races, for now.
            // Bat villages, while awesome, should not happen.
            if (race && race->get_user_playable())
            {
              village_tile->set_village_race_id(race_id);
              village_tile->set_settlement_type(race->get_settlement_type());
              village_tile->set_tile_subtype(race->get_settlement_tile_subtype());                
            }

            unused_initial_race_ids.erase(race_id_it);
            break;
          }
            
          count++;
        }
      }
      else
      {
        // All the races are selected (one of each), so now take one at random
        // from the game's current races, ensuring that it is user-playable.
        vector<string> playable_race_ids;

        for (const RaceMap::value_type& pr : races)
        {
          if (pr.second->get_user_playable())
          {
            playable_race_ids.push_back(pr.first);
          }
        }

        int rand_race_idx = RNG::range(0, playable_race_ids.size()-1);
        string race_id = playable_race_ids.at(rand_race_idx);

        village_tile->set_village_race_id(race_id);
        village_tile->set_tile_subtype(races[race_id]->get_settlement_tile_subtype());
      }
    }
  }
}

// Generate the surroundings for each village
void WorldGenerator::generate_village_surroundings(MapPtr map)
{
  Dimensions dim = map->size();
  Game& game = Game::instance();
  
  RaceMap races = game.get_races_ref();
  DeityMap deities = game.get_deities_ref();
    
  for (const Coordinate& c : village_coordinates)
  {
    bool worship_site_generated = false;
      
    int village_row = c.first;
    int village_col = c.second;
      
    // For each village in the initial set, ensure that its village_race_id is 
    // set to one of the unused_initial_race_ids, and then remove that ID from the set.
    TilePtr tile = map->at(village_row, village_col);
    VillageTilePtr village_tile = dynamic_pointer_cast<VillageTile>(tile);
      
    if (village_tile)
    {
      string race_id = village_tile->get_village_race_id();
        
      // Get the adjacent tiles
      vector<Coordinate> adjacent_to_village = CoordUtils::get_adjacent_map_coordinates(dim, village_row, village_col);
        
      for (const Coordinate& c2 : adjacent_to_village)
      {
        int adjacent_row = c2.first;
        int adjacent_col = c2.second;
          
        TilePtr adjacent_village_tile = map->at(adjacent_row, adjacent_col);
        TileType adjacent_type = adjacent_village_tile->get_tile_type();
          
        if (adjacent_type != TILE_TYPE_SEA && adjacent_type != TILE_TYPE_VILLAGE)
        {
          // 20% chance of a worship site.  Generate a site based on a randomly
          // selected deity allowable for the village's race.
          if (!worship_site_generated && RNG::percent_chance(20))
          {
            vector<string> initial_deity_ids = races[race_id]->get_initial_deity_ids();
            int deity_id_idx = RNG::range(0, initial_deity_ids.size()-1);
            string deity_id = initial_deity_ids[deity_id_idx];
            DeityPtr deity = deities[deity_id];
            WorshipSiteTilePtr site_tile = tg.generate_worship_site_tile(deity->get_alignment_range(), deity_id, deity->get_worship_site_type());
            map->insert(adjacent_row, adjacent_col, site_tile);
            worship_site_generated = true;
          }
        }
      }    
    }    
  }
}

void WorldGenerator::remove_village_coordinates_if_present(const Coordinate& c)
{
  if (!village_coordinates.empty())
  {
    set<Coordinate>::iterator it = village_coordinates.find(c);
    
    if (it != village_coordinates.end())
    {
      village_coordinates.erase(it);
    }
  }
}

MapType WorldGenerator::get_map_type() const
{
  return MAP_TYPE_WORLD;
}
