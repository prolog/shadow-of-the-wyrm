#include <vector>
#include "AlignmentEnums.hpp"
#include "CastleGenerator.hpp"
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "CreatureGenerationConstants.hpp"
#include "CreatureGenerationOptionsStringBuilder.hpp"
#include "DungeonGenerator.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "WorldGenerator.hpp"
#include "PlayerConstants.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "CellularAutomataGenerator.hpp"
#include "MapProperties.hpp"
#include "Serialize.hpp"
#include "VillageTile.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using std::dynamic_pointer_cast;

const int WorldGenerator::MIN_CREATURES_PER_VILLAGE = 12;
const int WorldGenerator::MAX_CREATURES_PER_VILLAGE = 26;

// Even though the map_terrain_type parameter is used to generate creatures, and UNDEFINED would normally be bad, it
// shouldn't matter for the world, since there will never be creatures generated on it.
//
// The tile generator should not generate any random items on the world map!
// Those items cannot be picked up.
WorldGenerator::WorldGenerator()
: Generator("", TileType::TILE_TYPE_UNDEFINED), tg(false)
{
}

WorldGenerator::WorldGenerator(const string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_UNDEFINED)
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
  initial_race_ids.clear();
  
  MapPtr result_map = std::make_shared<Map>(dimensions);

  // Fill the world with water.
  fill(result_map, TileType::TILE_TYPE_SEA);

  // Generate the random world
  result_map = generate_random_islands(result_map);

  // Generate villages and their surroundings
  populate_race_information();
  set_village_races(result_map);
  generate_village_surroundings(result_map);  
  
  result_map->set_map_type(MapType::MAP_TYPE_WORLD);
  result_map->set_map_id(MapID::MAP_ID_OVERWORLD);
  result_map->set_permanent(true);

  return result_map;
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
  CellularAutomataSettings cas(55, 50000, 4, 54, CellValue::CELL_OFF);
  CellularAutomataGenerator cag(cas, dimensions);
  field_cell_map = cag.generate();

  // Forests
  CellularAutomataSettings cas_forest(52, 50000, 4, 54, CellValue::CELL_OFF);
  CellularAutomataGenerator cag_forest(cas_forest, dimensions);
  forest_cell_map = cag_forest.generate();
  
  // Hills
  CellularAutomataSettings cas_hills(51, 50000, 4, 54, CellValue::CELL_OFF);
  CellularAutomataGenerator cag_hills(cas_hills, dimensions);
  hills_cell_map = cag_hills.generate();

  // Mountains
  CellularAutomataSettings cas_mountains(45, 50000, 4, 45, CellValue::CELL_ON);
  CellularAutomataGenerator cag_mountains(cas_mountains, dimensions);
  mountains_cell_map = cag_mountains.generate();

  // Scrubland
  CellularAutomataSettings cas_scrub(53, 50000, 4, 53, CellValue::CELL_OFF);
  CellularAutomataGenerator cag_scrub(cas_scrub, dimensions);
  scrub_cell_map = cag_scrub.generate();
  
  // Marshes
  CellularAutomataSettings cas_marsh(20, 100, 4, 20, CellValue::CELL_OFF);
  CellularAutomataGenerator cag_marsh(cas_marsh, dimensions);
  marsh_cell_map = cag_marsh.generate();
  
  // Desert
  CellularAutomataSettings cas_desert(20, 100, 4, 20, CellValue::CELL_OFF);
  CellularAutomataGenerator cag_desert(cas_desert, dimensions);
  desert_cell_map = cag_desert.generate();
}

// Handle generation of field terrain
void WorldGenerator::process_field_cell(MapPtr result_map, const int row, const int col, const CellValue world_val)
{  
  // Always add fields.  
  if (world_val == CellValue::CELL_OFF)
  {
    TilePtr tile;

    vector<pair<int, pair<TileType, TileType>>> field_special_types;
    field_special_types = {{200, {TileType::TILE_TYPE_DUNGEON_COMPLEX, TileType::TILE_TYPE_UNDEFINED}},
                           {200, {TileType::TILE_TYPE_CRYPT, TileType::TILE_TYPE_UNDEFINED}},
                           {300, {TileType::TILE_TYPE_CASTLE, TileType::TILE_TYPE_FIELD}},
                           {300, {TileType::TILE_TYPE_KEEP, TileType::TILE_TYPE_FIELD}},
                           {100, {TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_FIELD}}};

    tile = generate_feature_or_default(field_special_types, TileType::TILE_TYPE_FIELD, row, col);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::set_tile_properties(TilePtr tile, TileType tile_type, TileType tile_subtype, const int row, const int col)
{
  Coordinate c = make_pair(row, col);

  if (tile_type == TileType::TILE_TYPE_VILLAGE)
  {
    village_coordinates.insert(c);
  }
  else
  {
    remove_village_coordinates_if_present(c);

    if (tile_type == TileType::TILE_TYPE_KEEP)
    {
      bool ruined = RNG::percent_chance(50);

      // Set the ruined flag, if applicable, so that when the generator is
      // created, the keep can be generated either ruined or upright.
      if (ruined)
      {
        tile->set_additional_property(TileProperties::TILE_PROPERTY_RUINED, Bool::to_string(ruined));
      }
    }
    else if (tile_type == TileType::TILE_TYPE_CASTLE)
    {
      CastleType ct = static_cast<CastleType>(RNG::range(static_cast<int>(CastleType::CASTLE_TYPE_MOTTE_AND_BAILEY), static_cast<int>(CastleType::CASTLE_TYPE_LAST)));
      tile->set_additional_property(TileProperties::TILE_PROPERTY_CASTLE_TYPE, std::to_string(static_cast<int>(ct)));
    }
  }
}

void WorldGenerator::process_hill_cell(MapPtr result_map, const int row, const int col, const CellValue hills_val, const CellValue world_val)
{
  if (hills_val == CellValue::CELL_OFF && world_val == CellValue::CELL_OFF)
  {
    TilePtr tile;

    vector<pair<int, pair<TileType, TileType>>> hill_special_types;
    hill_special_types = { { 100, { TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_HILLS } },
                           { 300, { TileType::TILE_TYPE_KEEP, TileType::TILE_TYPE_HILLS } } };

    tile = generate_feature_or_default(hill_special_types, TileType::TILE_TYPE_HILLS, row, col);
    result_map->insert(row, col, tile);
  }
}

TilePtr WorldGenerator::generate_feature_or_default(const vector<pair<int, pair<TileType, TileType>>>& special_types, TileType default_tile_type, const int row, const int col)
{
  TilePtr result;

  for (const auto& sp_type_pair : special_types)
  {
    if (RNG::x_in_y_chance(1, sp_type_pair.first))
    {
      TileType tile_type = sp_type_pair.second.first;
      TileType tile_subtype = sp_type_pair.second.second;

      result = tg.generate(tile_type, tile_subtype);
      set_tile_properties(result, tile_type, tile_subtype, row, col);

      break;
    }
  }

  if (result == nullptr)
  {
    result = tg.generate(default_tile_type, TileType::TILE_TYPE_UNDEFINED);
    set_tile_properties(result, default_tile_type, TileType::TILE_TYPE_UNDEFINED, row, col);
  }

  return result;
}

void WorldGenerator::process_marsh_cell(MapPtr result_map, const int row, const int col, const CellValue marsh_val, const CellValue world_val)
{  
  if (marsh_val == CellValue::CELL_OFF && world_val == CellValue::CELL_OFF)
  {
    TilePtr tile;

    vector<pair<int, pair<TileType, TileType>>> marsh_special_types;
    marsh_special_types = { { 200, { TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_MARSH } } };

    tile = generate_feature_or_default(marsh_special_types, TileType::TILE_TYPE_MARSH, row, col);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_forest_cell(MapPtr result_map, const int row, const int col, const CellValue forest_val, const CellValue world_val)
{  
  if (forest_val == CellValue::CELL_OFF && world_val == CellValue::CELL_OFF)
  {
    TilePtr tile;

    vector<pair<int, pair<TileType, TileType>>> forest_special_types;
    forest_special_types = { { 100, { TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_FOREST } },
                            { 50, { TileType::TILE_TYPE_WILD_ORCHARD, TileType::TILE_TYPE_UNDEFINED } },
                            { 250, { TileType::TILE_TYPE_CASTLE, TileType::TILE_TYPE_UNDEFINED } } };

    tile = generate_feature_or_default(forest_special_types, TileType::TILE_TYPE_FOREST, row, col);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_scrub_cell(MapPtr result_map, const int row, const int col, const CellValue scrub_val, const CellValue world_val)
{   
  if (scrub_val == CellValue::CELL_OFF && world_val == CellValue::CELL_OFF)
  {
    TilePtr tile;

    vector<pair<int, pair<TileType, TileType>>> scrub_special_types;
    scrub_special_types = { { 200, { TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_SCRUB } },
                            { 300, { TileType::TILE_TYPE_KEEP, TileType::TILE_TYPE_SCRUB } } };

    tile = generate_feature_or_default(scrub_special_types, TileType::TILE_TYPE_SCRUB, row, col);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_desert_cell(MapPtr result_map, const int row, const int col, const CellValue desert_val, const CellValue scrub_val, const CellValue world_val)
{
  TilePtr tile;
  
  // Deserts should only appear in naturally dry areas.
  if (desert_val == CellValue::CELL_OFF && world_val == CellValue::CELL_OFF && scrub_val == CellValue::CELL_OFF)
  {
    tile = generate_feature_or_default({}, TileType::TILE_TYPE_DESERT, row, col);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::process_mountain_cell(MapPtr result_map, const int row, const int col, const CellValue mountains_val, const CellValue forest_val, const CellValue world_val)
{
  if (mountains_val == CellValue::CELL_OFF && world_val == CellValue::CELL_OFF && forest_val == CellValue::CELL_ON)
  {
    // 2% chance of being a dungeon or crypt
    // 3% chance of being a cavern
    TilePtr tile;

    vector<pair<int, pair<TileType, TileType>>> mountain_special_types;
    mountain_special_types = { { 50, { TileType::TILE_TYPE_DUNGEON_COMPLEX, TileType::TILE_TYPE_UNDEFINED } },
                               { 50, { TileType::TILE_TYPE_CRYPT, TileType::TILE_TYPE_UNDEFINED } },
                               { 33, { TileType::TILE_TYPE_CAVERN, TileType::TILE_TYPE_UNDEFINED } } };

    tile = generate_feature_or_default(mountain_special_types, TileType::TILE_TYPE_MOUNTAINS, row, col);
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
      
    if (race && race->get_user_playable() && race->get_has_random_villages() && !current_race_id.empty())
    {
      initial_race_ids.insert(current_race_id);
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
      int rand_race_id_idx = RNG::range(0, initial_race_ids.size()-1);
      set<string>::iterator race_id_it;
          
      int count = 0;
      for (race_id_it = initial_race_ids.begin(); race_id_it != initial_race_ids.end(); race_id_it++)
      {
        if (count == rand_race_id_idx)
        {
          string race_id = *race_id_it;
          RacePtr race = races[race_id];
             
          // The population of the initial_race_ids set takes into consideration
          // that races must be user-playable (no bat villages!) and must allow
          // random villages - some races - Fae, for instance) don't have any
          // random villages.
          if (race != nullptr)
          {
            village_tile->set_village_race_id(race_id);
            village_tile->set_settlement_type(race->get_settlement_type());
            village_tile->set_tile_subtype(race->get_settlement_tile_subtype());

            set_initial_creatures_for_village(village_tile, race_id);

            ostringstream log_msg;
            log_msg << "Creatures for village at " << c.first << "," << c.second << " with race_id " << race_id << ": " << village_tile->get_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
            Log::instance().debug(log_msg.str());
          }

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

      if (village_tile != nullptr)
      {
        village_tile->set_village_race_id(race_id);
        village_tile->set_tile_subtype(races[race_id]->get_settlement_tile_subtype());
      }
      else
      {
        ostringstream ss;
        ss << "Could not create village at " << c.first << "," << c.second << ".  Tile type is " << static_cast<int>(tile->get_tile_type());
        Log::instance().error(ss.str());
      }
    }
  }
}

// Set the initial list of creatures for the village tile.
void WorldGenerator::set_initial_creatures_for_village(TilePtr tile, const string& village_race_id)
{
  // Get the list of potential creatures.
  vector<string> creature_ids = get_potential_creatures(village_race_id);

  // Create the list of creatures on the village tile.
  set_creatures_to_village_tile(tile, creature_ids);
}

// Get a list of all potential creatures for the village: must allow TILE_TYPE_VILLAGE,
// the race ID must match, and they must not have hit the max number of generated
// creatures at the time this function runs.
vector<string> WorldGenerator::get_potential_creatures(const string& village_race_id)
{
  vector<string> valid_creature_ids;
  Game& game = Game::instance();
  CreatureGenerationValuesMap& cgv_map = game.get_creature_generation_values_ref();

  for (const auto& cgv_pair : cgv_map)
  {
    string race_id = cgv_pair.second.get_race_id();
    set<TileType> allowable_terrain = cgv_pair.second.get_allowable_terrain_types();
    int max = cgv_pair.second.get_maximum();

    if (allowable_terrain.find(TileType::TILE_TYPE_VILLAGE) != allowable_terrain.end() 
     && race_id == village_race_id
     && (max == CreatureGenerationConstants::CREATURE_GENERATION_UNLIMITED || cgv_pair.second.get_current() < max))
    {
      CreatureGenerationOptions cgo;
      cgo.set_id(cgv_pair.first);

      // All creatures generated in villages should be docile.
      cgo.set_hostility(PlayerConstants::PLAYER_CREATURE_ID, false);

      CreatureGenerationOptionsStringBuilder cgob;
      valid_creature_ids.push_back(cgob.build(cgo));
    }
  }

  return valid_creature_ids;
}

// Generate a random number of creatures from the provided vector of valid
// creature IDs, and set them on the village tile.
void WorldGenerator::set_creatures_to_village_tile(TilePtr tile, const vector<string>& valid_creature_ids)
{
  if (!valid_creature_ids.empty())
  {
    vector<string> creatures_to_gen;
    int num_creatures = RNG::range(MIN_CREATURES_PER_VILLAGE, MAX_CREATURES_PER_VILLAGE);
    size_t max_creature_idx = valid_creature_ids.size() - 1;

    for (int i = 0; i < num_creatures; i++)
    {
      creatures_to_gen.push_back(valid_creature_ids.at(RNG::range(0, max_creature_idx)));
    }

    string creatures_csv = String::create_csv_from_string_vector(creatures_to_gen);
    tile->set_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES, creatures_csv);
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
    // set to one of the initial_race_ids.
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
          
        if (adjacent_type != TileType::TILE_TYPE_SEA && adjacent_type != TileType::TILE_TYPE_VILLAGE)
        {
          // 20% chance of a worship site.  Generate a site based on a randomly
          // selected deity allowable for the village's race.
          if (!worship_site_generated && RNG::percent_chance(20))
          {
            ostringstream log_ss;

            if (!race_id.empty())
            {
              vector<string> initial_deity_ids = races[race_id]->get_initial_deity_ids();
              int deity_id_idx = RNG::range(0, initial_deity_ids.size() - 1);
              string deity_id = initial_deity_ids[deity_id_idx];
              DeityPtr deity = deities[deity_id];
              WorshipSiteTilePtr site_tile = tg.generate_worship_site_tile(deity->get_alignment_range(), deity_id, deity->get_worship_site_type());
              map->insert(adjacent_row, adjacent_col, site_tile);
              worship_site_generated = true;

              log_ss << "Created worship site for deity ID " << deity_id << " at " << adjacent_row << "," << adjacent_col;
              Log::instance().debug(log_ss.str());
            }
            else
            {
              log_ss << "Could not create worship site at " << adjacent_row << "," << adjacent_col << " due to empty race_id.";
              Log::instance().error(log_ss.str());
            }
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
  return MapType::MAP_TYPE_WORLD;
}
