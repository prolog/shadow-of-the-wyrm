#include <vector>
#include "AlignmentEnums.hpp"
#include "CastleGenerator.hpp"
#include "CellularAutomataGenerator.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureGenerationConstants.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureGenerationOptionsStringBuilder.hpp"
#include "DungeonGenerator.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "Naming.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"
#include "TextMessages.hpp"
#include "TileGenerator.hpp"
#include "TileTextKeys.hpp"
#include "VillageTile.hpp"
#include "WorldGenerator.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using std::dynamic_pointer_cast;

void async_worldgen(std::promise<MapPtr>&& mp)
{
  WorldGenerator world_generator;
  mp.set_value(world_generator.generate());
}

const int WorldGenerator::MIN_CREATURES_PER_VILLAGE = 12;
const int WorldGenerator::MAX_CREATURES_PER_VILLAGE = 26;
const int WorldGenerator::MAX_DANGER_LEVEL_FOR_WORLD_GEN = 50;
const pair<int, int> WorldGenerator::X_IN_Y_CHANCE_TREASURE = { 1, 100 };

// Even though the map_terrain_type parameter is used to generate creatures, and UNDEFINED would normally be bad, it
// shouldn't matter for the world, since there will never be creatures generated on it.
//
// The tile generator should not generate any random items on the world map!
// Those items cannot be picked up.
WorldGenerator::WorldGenerator()
: Generator("", TileType::TILE_TYPE_UNDEFINED)
, tile_property_fns({{TileType::TILE_TYPE_DUNGEON_COMPLEX, &WorldGenerator::set_dungeon_complex_properties},
                     {TileType::TILE_TYPE_KEEP, &WorldGenerator::set_keep_properties},
                     {TileType::TILE_TYPE_CASTLE, &WorldGenerator::set_castle_properties},
                     {TileType::TILE_TYPE_SEWER, &WorldGenerator::set_sewer_complex_properties}})
// Min Depth for dungeons is 10 levels, 5 for sewers.  Caverns have the most
// variance, and can be anywhere from 1 to 50 levels deep.
, tile_depth_options({{TileType::TILE_TYPE_DUNGEON_COMPLEX, TileDepthOptions(10, 50, vector<int>({50, 45}))},
                      {TileType::TILE_TYPE_SEWER_COMPLEX, TileDepthOptions(5, 50, vector<int>({50}))},
                      {TileType::TILE_TYPE_CAVERN, TileDepthOptions(1, 50)},
                      {TileType::TILE_TYPE_MINE, TileDepthOptions(5, 50, vector<int>({50,30}))}})
  , tg(false)
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
  MapPtr result_map = std::make_shared<Map>(dimensions);

  result_map->set_permanent(true);
  result_map->set_map_type(MapType::MAP_TYPE_WORLD);
  result_map->set_map_id(MapID::MAP_ID_WORLD_MAP);

  // Clear the state variables, in case this generator has already had a run.
  village_coordinates.clear();
  initial_race_ids.clear();
  
  // Fill the world with water.
  fill(result_map, TileType::TILE_TYPE_SEA);

  // Generate the random world
  result_map = generate_random_islands(result_map);

  // Generate villages and their surroundings
  populate_race_information();
  set_village_races(result_map);
  generate_village_surroundings(result_map);    

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

      post_process_cell(result_map, row, col);
    }
  }

  return result_map;
}

void WorldGenerator::post_process_cell(MapPtr map, const int row, const int col)
{
  TilePtr tile = map->at(row, col);
  TileType tt = tile->get_tile_type();
  vector<pair<int, pair<string, string>>> prop_pairs;

  if (tt == TileType::TILE_TYPE_FIELD)
  {
    prop_pairs = { {250, {TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR, TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR}},
                   {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE}},
                   {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE}},
                   {250, {TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE, TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE}}};
  }
  else if (tt == TileType::TILE_TYPE_HILLS)
  {
    prop_pairs = { {400, {TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR, TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR}},
                   {500, {TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE}},
                   {350, {TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE, TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE}}};
  }
  else if (tt == TileType::TILE_TYPE_MARSH)
  {
    prop_pairs = { {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE}},
                   {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE}}
    };
  }
  else if (tt == TileType::TILE_TYPE_FOREST)
  {
    prop_pairs = { {300, {TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE}},
                   {300, {TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE}},
    };
  }
  else if (tt == TileType::TILE_TYPE_SCRUB)
  {
    prop_pairs = { {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR, TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR}},
                   {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE}},
                   {450, {TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE, TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE}} };
  }
  else if (tt == TileType::TILE_TYPE_DESERT)
  {
    prop_pairs = { {100, {TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR, TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR}},
                   {600, {TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE, TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE}} };
  }
  // else { ... }
  // Mountains and all other terrain types don't have properties currently
  // defined.

  potentially_add_properties(row, col, tile, prop_pairs);
}

void WorldGenerator::potentially_add_properties(const int row, const int col, TilePtr tile, const vector<pair<int, pair<string, string>>>& prob_and_props)
{
  if (tile != nullptr)
  {
    for (const auto& p_pair : prob_and_props)
    {
      if (RNG::x_in_y_chance(1, p_pair.first))
      {
        if (Log::instance().debug_enabled())
        {
          ostringstream ss;
          ss << "Generated " << p_pair.second.first << " at " << row << "," << col << " for tile type " << static_cast<int>(tile->get_tile_type());

          Log::instance().debug(ss.str());
        }

        tile->set_additional_property(p_pair.second.first, p_pair.second.second);
      }
    }
  }
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
                           {400, {TileType::TILE_TYPE_SEWER_COMPLEX, TileType::TILE_TYPE_UNDEFINED}},
                           {500, {TileType::TILE_TYPE_GRAVEYARD, TileType::TILE_TYPE_UNDEFINED}},
                           {100, {TileType::TILE_TYPE_VILLAGE, TileType::TILE_TYPE_FIELD}}};

    tile = generate_feature_or_default(field_special_types, TileType::TILE_TYPE_FIELD, row, col);
    result_map->insert(row, col, tile);
  }
}

void WorldGenerator::set_tile_properties(TilePtr tile, TileType tile_type, const int row, const int col)
{
  Coordinate c = make_pair(row, col);

  if (tile_type == TileType::TILE_TYPE_VILLAGE)
  {
    village_coordinates.insert(c);
  }
  else
  {
    remove_village_coordinates_if_present(c);
  }

  if (tile != nullptr)
  {
    auto t_it = tile_property_fns.find(tile->get_tile_type());

    if (t_it != tile_property_fns.end())
    {
      (this->*(t_it->second))(tile);
    }

    set_tile_depth_details(tile);
  }
}

void WorldGenerator::set_tile_depth_details(TilePtr tile)
{
  if (tile != nullptr)
  {
    TileType tt = tile->get_tile_type();

    auto t_it = tile_depth_options.find(tt);

    if (t_it != tile_depth_options.end())
    {
      TileDepthOptions& tdo = t_it->second;
      int max_depth = 1;

      set_tile_depth_options(tile, tdo, max_depth);
      set_tile_depth_creature_details(tile, max_depth);
    }
  }
}

void WorldGenerator::set_tile_depth_options(TilePtr tile, TileDepthOptions& tdo, int& max_depth)
{
  if (tile != nullptr)
  {
    vector<int>& remaining_depths = tdo.get_remaining_depths_ref();

    if (!remaining_depths.empty())
    {
      max_depth = remaining_depths.back();
      remaining_depths.pop_back();
    }
    else
    {
      max_depth = RNG::range(tdo.get_min_depth(), tdo.get_max_depth());
    }

    // Set the max depth on the tile.
    tile->set_additional_property(MapProperties::MAP_PROPERTIES_MAX_DEPTH, to_string(max_depth));
  }
}

void WorldGenerator::set_tile_depth_creature_details(TilePtr tile, const int max_depth)
{
  if (tile != nullptr)
  {
    TileType tile_type = tile->get_tile_type();

    CreatureGenerationIndex gindex;
    CreatureGenerationList generation_list;
    auto cgm_cache_it = creature_generation_map_cache.find(tile_type);

    if (cgm_cache_it != creature_generation_map_cache.end())
    {
      generation_list = cgm_cache_it->second.get(max_depth);
    }
    else
    {
      // Get a creature ID for the given tile/depth combination.
      // Cache it so that performance isn't brutal.
      CreatureGenerationManager cgm;
      gindex = cgm.generate_creature_generation_map({ tile_type }, true /* assume permanent */, false /* assume not islet */, MapType::MAP_TYPE_UNDERWORLD /* assume not underwater */, 1, MAX_DANGER_LEVEL_FOR_WORLD_GEN, Rarity::RARITY_COMMON, {});
      generation_list = gindex.get(max_depth);

      creature_generation_map_cache.emplace(tile_type, gindex);
    }

    if (!generation_list.empty())
    {
      int rnd_val = RNG::range(0, generation_list.size() - 1);
      const CreatureGenerationListValue& cglv = generation_list.at(rnd_val);

      CreaturePtr creature = cglv.get_creature();

      if (creature != nullptr)
      {
        tile->set_additional_property(TileProperties::TILE_PROPERTY_ENGRAVING_SID, creature->get_description_sid());
      }
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
                           { 300, { TileType::TILE_TYPE_KEEP, TileType::TILE_TYPE_HILLS } },
                           { 650, { TileType::TILE_TYPE_GRAVEYARD, TileType::TILE_TYPE_UNDEFINED } } };

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
      set_tile_properties(result, tile_type, row, col);

      ostringstream ss;
      ss << "Generated tile type " << static_cast<int>(tile_type) << " at (" << row << "," << col << ")";
      Log::instance().debug(ss.str());

      break;
    }
  }

  if (result == nullptr)
  {
    result = tg.generate(default_tile_type, TileType::TILE_TYPE_UNDEFINED);
    set_tile_properties(result, default_tile_type, row, col);
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
                            { 250, { TileType::TILE_TYPE_CASTLE, TileType::TILE_TYPE_UNDEFINED } },
                            { 650, { TileType::TILE_TYPE_GRAVEYARD, TileType::TILE_TYPE_UNDEFINED } } };

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
                            { 300, { TileType::TILE_TYPE_KEEP, TileType::TILE_TYPE_SCRUB } },
                            { 500, { TileType::TILE_TYPE_GRAVEYARD, TileType::TILE_TYPE_UNDEFINED } } };

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
                               { 60, { TileType::TILE_TYPE_MINE, TileType::TILE_TYPE_UNDEFINED } },
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
  
  const RaceMap& races = game.get_races_ref();
    
  for (const auto& r_pair : races)
  {
    string current_race_id = r_pair.first;
    Race* race = r_pair.second.get();
      
    if (race && race->get_user_playable() && race->get_has_random_villages() && !current_race_id.empty())
    {
      initial_race_ids.insert(current_race_id);
      village_race_sids[current_race_id] = race->get_race_settlement_sid();
    }
  }
}

// JCD FIXME: Unwieldy, refactor.
void WorldGenerator::set_village_races(MapPtr map)
{
// Sometimes useful to know:
//  int total_villages = village_coordinates.size();

  Game& game = Game::instance();
  const RaceMap& races = game.get_races_ref();
  RaceManager rm;

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
          Race* race = rm.get_race(race_id);
             
          // The population of the initial_race_ids set takes into consideration
          // that races must be user-playable (no bat villages!) and must allow
          // random villages - some races - Fae, for instance) don't have any
          // random villages.
          if (race != nullptr)
          {
            village_tile->set_village_race_id(race_id);
            village_tile->set_settlement_type(race->get_settlement_type());
            village_tile->set_tile_subtype(race->get_settlement_tile_subtype());
            village_tile->set_extra_description_sid(get_race_village_extra_description_sid(race_id));

            string settlement_name = Naming::generate_settlement_name();
            village_tile->set_village_name(settlement_name);

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
      Race* race = rm.get_race(race_id);

      if (village_tile != nullptr && race != nullptr)
      {
        village_tile->set_village_race_id(race_id);
        village_tile->set_tile_subtype(race->get_settlement_tile_subtype());
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
      cgo.set_hostility(CreatureID::CREATURE_ID_PLAYER, false);

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
  
  const DeityMap& deities = game.get_deities_cref();
  RaceManager rm;
    
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
              vector<string> initial_deity_ids = rm.get_race(race_id)->get_initial_deity_ids();
              int deity_id_idx = RNG::range(0, initial_deity_ids.size() - 1);
              string deity_id = initial_deity_ids[deity_id_idx];
              Deity* deity = nullptr;
              auto d_it = deities.find(deity_id);
              if (d_it != deities.end())
              {
                deity = d_it->second.get();
              }

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

void WorldGenerator::set_village_coordinates(MapPtr map)
{
  if (map != nullptr)
  {
    const TilesContainer& tiles = map->get_tiles_ref();
    vector<string> s_coords;

    for (const auto& t_pair : tiles)
    {
      if (t_pair.second && t_pair.second->get_tile_type() == TileType::TILE_TYPE_VILLAGE)
      {
        VillageTilePtr vt = dynamic_pointer_cast<VillageTile>(t_pair.second);

        if (vt != nullptr && !vt->get_name().empty())
        {
          s_coords.push_back(t_pair.first);
        }
      }
    }

    if (!s_coords.empty())
    {
      map->set_property(MapProperties::MAP_PROPERTIES_VILLAGE_COORDINATES, String::create_csv_from_string_vector(s_coords));
    }
  }
}

void WorldGenerator::set_treasure(MapPtr map)
{
  if (map != nullptr)
  {
    NormalDistribution forest_treasures(40, 12);
    NormalDistribution desert_treasures(50, 15);
    NormalDistribution marsh_treasures(60, 12);
    NormalDistribution underwater_treasures(70, 15);
    NormalDistribution mountain_treasures(80, 7);
    
    bool desert_override = true;
    bool forest_override = true;
    bool marsh_override = true;
    bool underwater_override = true;
    bool mountain_override = true;

    TilesContainer& tc = map->get_tiles_ref();
    
    for (const auto& tc_pair : tc)
    {
      // Ensure we're not adding treasure specifiers to tiles that already link
      // to another map.
      if (tc_pair.second != nullptr && tc_pair.second->get_custom_map_id().empty())
      {
        TileType tt = tc_pair.second->get_tile_type();

        if (tt == TileType::TILE_TYPE_SEA)
        {
          continue;
        }

        // Shipwrecks can appear underwater around any of the other treasure-
        // generating tile types. Determining if they can be placed requires
        // at least one cardinally-adjacent sea tile.
        Coordinate c = MapUtils::convert_map_key_to_coordinate(tc_pair.first);

        if (MapUtils::adjacent_tiles_contain_type(map, c, { Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST }, TileType::TILE_TYPE_SEA))
        {
          potentially_add_treasure(tc_pair.first, tc_pair.second, underwater_treasures, underwater_override, true);
        }

        if (tt == TileType::TILE_TYPE_DESERT)
        {
          potentially_add_treasure(tc_pair.first, tc_pair.second, desert_treasures, desert_override, false);
        }
        else if (tt == TileType::TILE_TYPE_FOREST)
        {
          potentially_add_treasure(tc_pair.first, tc_pair.second, forest_treasures, forest_override, false);
        }
        else if (tt == TileType::TILE_TYPE_MARSH)
        {
          potentially_add_treasure(tc_pair.first, tc_pair.second, marsh_treasures, marsh_override, false);
        }
        else if (tt == TileType::TILE_TYPE_MOUNTAINS)
        {
          potentially_add_treasure(tc_pair.first, tc_pair.second, mountain_treasures, mountain_override, false);
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

void WorldGenerator::set_dungeon_complex_properties(TilePtr tile)
{
  if (tile != nullptr)
  {
    // ...
  }
}

void WorldGenerator::set_sewer_complex_properties(TilePtr tile)
{
  if (tile != nullptr)
  {
    // ...
  }
}

void WorldGenerator::set_keep_properties(TilePtr tile)
{
  if (tile != nullptr)
  {
    bool ruined = RNG::percent_chance(50);

    // Set the ruined flag, if applicable, so that when the generator is
    // created, the keep can be generated either ruined or upright.
    if (ruined)
    {
      tile->set_additional_property(TileProperties::TILE_PROPERTY_RUINED, std::to_string(ruined));
    }
  }
}

void WorldGenerator::set_castle_properties(TilePtr tile)
{
  if (tile != nullptr)
  {
    CastleType ct = static_cast<CastleType>(RNG::range(static_cast<int>(CastleType::CASTLE_TYPE_MOTTE_AND_BAILEY), static_cast<int>(CastleType::CASTLE_TYPE_LAST)));
    tile->set_additional_property(TileProperties::TILE_PROPERTY_CASTLE_TYPE, std::to_string(static_cast<int>(ct)));
  }
}

string WorldGenerator::get_race_village_extra_description_sid(const string& race_id)
{
  string sid;
  auto r_it = village_race_sids.find(race_id);

  if (r_it != village_race_sids.end())
  {
    sid = r_it->second;
  }

  return sid;
}

void WorldGenerator::potentially_add_treasure(const string& key, TilePtr tile, NormalDistribution& nd, bool& terrain_override, const bool treasure_is_underwater)
{
  if (tile != nullptr && (terrain_override || RNG::x_in_y_chance(X_IN_Y_CHANCE_TREASURE.first, X_IN_Y_CHANCE_TREASURE.second)))
  {
    Log& log = Log::instance();
    int difficulty = nd.next_int_as_pct();
    string source = TextMessages::get_hidden_treasure_message(treasure_is_underwater);

    if (terrain_override)
    {
      terrain_override = false;
      int override_difficulty = RNG::range(85, 100);

      if (override_difficulty > difficulty)
      {
        difficulty = override_difficulty;
      }
    }

    if (log.debug_enabled())
    {
      ostringstream log_msg;
      log_msg << "Treasure: " << key << " (difficulty " << difficulty << ", uw=" << treasure_is_underwater << ")[" << source << "]";
      log.debug(log_msg.str());
    }

    if (treasure_is_underwater)
    {
      // ...
    }
    else
    {
      tile->set_additional_property(TileProperties::TILE_PROPERTY_MIN_LORE_REQUIRED, std::to_string(difficulty));
      tile->set_additional_property(TileProperties::TILE_PROPERTY_TREASURE_SOURCE, source);
    }
  }
}
