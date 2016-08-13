#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "DirectionUtils.hpp"
#include "Log.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapExitUtils.hpp"
#include "MapItemGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "Game.hpp"
#include "Generator.hpp"
#include "Map.hpp"
#include "MapUtils.hpp"
#include "Serialize.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using namespace SOTW;

const int Generator::FORAGABLE_MIN = 0;
const int Generator::FORAGABLE_MAX = 8;

Generator::Generator(const string& new_map_exit_id, const TileType new_map_terrain_type)
: map_exit_id(new_map_exit_id), map_terrain_type(new_map_terrain_type), danger_level(0)
{
}

// Always calls the version with both a danger_level and dimensions, so that
// everything is set up properly.
MapPtr Generator::generate_and_initialize(const int danger)
{
  danger_level = danger;
  Dimensions dim;
  return generate_and_initialize(danger, dim);
}

MapPtr Generator::generate_and_initialize(const int danger, const Depth& depth)
{
  danger_level = danger;

  Dimensions dim;
  dim.set_depth(depth);

  return generate_and_initialize(danger_level, dim);
}

MapPtr Generator::generate_and_initialize(const int danger, const Dimensions& dim)
{
  danger_level = danger;

  MapPtr map = generate(dim);
  initialize(map, danger_level);
  create_properties_and_copy_to_map(map);
  
  return map;
}

// Initializes essential map properties like terrain type, ID, and permanence.
void Generator::initialize(MapPtr map, const int danger_level)
{
  map->set_terrain_type(map_terrain_type);
  set_map_permanence(map);

  // If a generated map ID has been set, update the map ID with that.
  string generated_map_id = get_additional_property(MapProperties::MAP_PROPERTIES_GENERATED_MAP_ID);
  if (!generated_map_id.empty())
  {
    map->set_map_id(generated_map_id);
  }
}

// Creates the initial set of entities (creatures and items) present
// on the map.
void Generator::create_entities(MapPtr map, const int danger_level, const bool create_creatures, const bool create_items)
{
  tuple<bool, int, Rarity> creature_details(false, -1, Rarity::RARITY_COMMON);

  if (create_creatures)
  {
    MapCreatureGenerator mcg;
    creature_details = mcg.generate_creatures(map, danger_level, additional_properties);
  }

  if (create_items && can_create_initial_items())
  {
    generate_initial_items(map, danger_level, creature_details);
  }

  string foragables = get_additional_property(MapProperties::MAP_PROPERTIES_PCT_CHANCE_FORAGABLES);
  string herbs = get_additional_property(MapProperties::MAP_PROPERTIES_PCT_CHANCE_HERBS);

  std::map<ForagableType, string> foragable_chances = {{ForagableType::FORAGABLE_TYPE_FORAGABLES, foragables}, {ForagableType::FORAGABLE_TYPE_HERBS, herbs}};

  for (const auto& f_pair : foragable_chances)
  {
    string chance = f_pair.second;

    if (!chance.empty())
    {
      int pct_chance = String::to_int(chance);

      if (map->get_map_type() == MapType::MAP_TYPE_OVERWORLD && RNG::percent_chance(pct_chance))
      {
        generate_foragables(map, f_pair.first);
      }
    }
  }
}

MapPtr Generator::generate()
{
  Dimensions default_dimensions;
  MapPtr result_map = generate(default_dimensions);
  create_properties_and_copy_to_map(result_map);

  return result_map;
}

void Generator::set_terrain_type(const TileType new_map_terrain_type)
{
  map_terrain_type = new_map_terrain_type;
}

TileType Generator::get_terrain_type() const
{
  return map_terrain_type;
}

void Generator::fill(const MapPtr map, const TileType& tile_type)
{
  TileGenerator tg;
  Dimensions dim = map->size();

  int rows = dim.get_y();
  int cols = dim.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr current_tile = tg.generate(tile_type);
      map->insert(row, col, current_tile);
    }
  }
}

// Seed the initial items.  Returns true if the items were created, false otherwise.
// By default, no initial items are generated.  This function should be overridden
// for generators where this is expected (dungeons, maybe villages, etc).
bool Generator::generate_initial_items(MapPtr map, const int danger_level, const tuple<bool, int, Rarity>& creature_details)
{
  MapItemGenerator mig;
  return mig.generate_items(map, danger_level, creature_details);
}

bool Generator::update_items(MapPtr map, const int danger_level)
{
  // Do nothing.  Items should never be generated after the initial seeding -
  // they should only be dropped by creatures after that.
  return false;
}

void Generator::set_map_permanence(MapPtr map)
{
  if (map)
  {
    // If the map has not already been made permanent, set hte value based
    // on the generator's default.
    if (map->get_permanent() == false)
    {
      map->set_permanent(get_permanence_default());
    }

    update_map_permanence_from_additional_properties(map);
  }
}

void Generator::update_map_permanence_from_additional_properties(MapPtr map)
{
  if (map)
  {
    string permanence_flag = get_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE);

    if (!permanence_flag.empty())
    {
      string no_map_id;
      bool permanence = String::to_bool(permanence_flag);

      map->set_permanent(permanence);

      if (!permanence)
      {
        map->set_map_id(no_map_id);
      }
    }
  }
}

// By default, overworld.  Override as necessary.
MapType Generator::get_map_type() const
{
  return MapType::MAP_TYPE_OVERWORLD;
}

// Clear, set, and get additional properties.
void Generator::clear_additional_properties()
{
  additional_properties.clear();
}

void Generator::set_additional_property(const string& property_name, const string& property_value)
{
  additional_properties[property_name] = property_value;
}

void Generator::set_additional_properties(const map<string, string>& new_additional_properties)
{
  additional_properties = new_additional_properties;
}

string Generator::get_additional_property(const string& property_name) const
{
  string property_value;

  map<string, string>::const_iterator p_it = additional_properties.find(property_name);
  if (p_it != additional_properties.end())
  {
    property_value = p_it->second;
  }
  
  return property_value;
}

bool Generator::has_additional_property(const string& property_name) const
{
  return (additional_properties.find(property_name) != additional_properties.end());
}

// Maps are not permanent by default.  For certain map types (fields, forests, etc),
// this is okay.  For others (dungeons, graveyards - really, anything readily
// exploitable), permanence will need to be set.
bool Generator::get_permanence_default() const
{
  return false;
}

// If the permanence property has been set, check that, and then the default.
bool Generator::get_permanence() const
{
  bool result = get_permanence_default();
  string permanence_flag = get_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE);

  if (!permanence_flag.empty())
  {
    result = String::to_bool(permanence_flag);
  }

  return result;
}

bool Generator::can_create_initial_items() const
{
  return false;
}

bool Generator::place_up_staircase(MapPtr map, const int row, const int col, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location)
{
  return place_staircase(map, row, col, TileType::TILE_TYPE_UP_STAIRCASE, tile_subtype, direction, link_to_map_exit_id, set_as_player_default_location);
}

bool Generator::place_down_staircase(MapPtr map, const int row, const int col,const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location)
{
  bool placed = place_staircase(map, row, col, TileType::TILE_TYPE_DOWN_STAIRCASE, tile_subtype, direction, link_to_map_exit_id, set_as_player_default_location);
  
  TilePtr tile = map->at(row, col);

  if (tile != nullptr)
  {
    tile->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));
    tile->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH, get_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH));
  }
  else
  {
    placed = false;
  }

  return placed;
}

bool Generator::place_staircase(MapPtr map, const int row, const int col, const TileType tile_type, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location)
{
  TileGenerator tg;
  TilePtr tile = map->at(row, col);
  
  // Don't overwrite an existing staircase!
  if (tile && (!tile->get_is_staircase()))
  {
    Coordinate c(row, col);
    
    TilePtr new_staircase_tile = tg.generate(tile_type);
    
    // If something's been generated on the original tile, make sure that it
    // makes its way to the new one.
    if (tile->has_feature())
    {
      new_staircase_tile->set_feature(tile->get_feature());
    }

    new_staircase_tile->set_tile_subtype(tile_subtype);

    // Allow for "infinite dungeons" by setting the permanence flag on the staircases, which will then get copied 
    // to the next generator, which will then set it on the down staircase...
    new_staircase_tile->set_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE, get_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE));

    map->insert(row, col, new_staircase_tile); 

    Depth depth = map->size().depth();

    // Handle exiting to a previous map in underworld maps like dungeons,
    // mines, crypts, etc.
    if (get_map_type() == MapType::MAP_TYPE_UNDERWORLD && tile_type == TileType::TILE_TYPE_UP_STAIRCASE)
    {
      // This may be empty, in which case, the custom map ID will be empty
      // and terrain will be checked instead, which is the desired behaviour.
      new_staircase_tile->set_custom_map_id(get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID));
      new_staircase_tile->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));

      // If we're on level 1, set the custom map ID to be the original map ID.
      if (depth.get_current() <= 1)
      {
        string original_map_id = get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID);
        new_staircase_tile->set_custom_map_id(original_map_id);
      }
    }
    else
    {
      // Handle the case where we need to link the new staircase to custom levels.
      set_custom_map_id_for_depth(new_staircase_tile, direction, depth, map->get_map_id());
      set_depth_custom_map_id_properties(new_staircase_tile);
    }

    add_tile_exit(map, std::make_pair(row, col), direction, link_to_map_exit_id);

    if (set_as_player_default_location)
    {
      map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
    }

    return true;
  }  
  
  return false;
}

// Copy the depth custom map ID properties over, so that when generating new staircases,
// custom map IDs for deep levels are preserved.  E.g., when generating a down staircase
// on level 1, ensure that the custom map IDs for level 5, 17, etc., get carried over.
void Generator::set_depth_custom_map_id_properties(TilePtr tile)
{
  for (const auto& pair : additional_properties)
  {
    if (TileProperties::is_depth_custom_map_id(pair.first))
    {
      tile->set_additional_property(pair.first, pair.second);
    }
  }
}

// Add an appropriate exit to the given tile, based on whether we should:
//
// - Link to the map exit ID specified on the generator
// - Link to a custom map ID for a particular depth
// - Or have no custom map ID, and instead generate based on tile type
void Generator::add_tile_exit(MapPtr map, const Coordinate& c, const Direction direction, const bool link_to_map_id)
{
  TilePtr tile = map->at(c);
  string tile_map_id;
  
  if (tile)
  {
    tile_map_id = tile->get_custom_map_id();
  }

  if (link_to_map_id && !map_exit_id.empty())
  {
    MapExitUtils::add_exit_to_tile(map, c, direction, map_exit_id);
  }
  // Otherwise, if we're not linking to a map exit ID, we should map to a tile exit.
  else
  {
    if (!tile_map_id.empty())
    {
      MapExitUtils::add_exit_to_tile(map, c, direction, tile_map_id);
    }
    else
    {
      MapExitUtils::add_exit_to_tile(map, c, direction, tile->get_tile_type());
    }
  }
}

// Get the custom map ID for a particular depth, and set it as the custom map ID
// for the given tile.
void Generator::set_custom_map_id_for_depth(TilePtr new_tile, const Direction exit_direction, const Depth& depth, const string& linkback_map_id)
{
  Depth new_depth = depth;
  TileType tile_type = new_tile->get_tile_type();

  if (tile_type == TileType::TILE_TYPE_UP_STAIRCASE)
  {
    new_depth = depth.higher();
  }
  else if (tile_type == TileType::TILE_TYPE_DOWN_STAIRCASE)
  {
    new_depth = depth.lower();
  }

  int new_d = new_depth.get_current();

  string depth_key = TileProperties::get_depth_custom_map_id(new_d);
  if (has_additional_property(depth_key))
  {
    // Set the value that has been specified on the generator, but only
    // if there's no custom map ID already set (e.g., level 1 up staircase
    // in an underworld level, which will have been mapped to point to 
    // the overworld map.
    string depth_map_id = get_additional_property(depth_key);
    string existing_depth_map_id = new_tile->get_custom_map_id();

    if (existing_depth_map_id.empty())
    {
      new_tile->set_custom_map_id(depth_map_id);
    }

    update_custom_map_with_current(depth_map_id, exit_direction, linkback_map_id, new_depth);
  }
}

void Generator::update_custom_map_with_current(const string& depth_map_id, const Direction exit_direction, const string& linkback_map_id, const Depth& new_depth)
{
  Game& game = Game::instance();
  MapRegistry& mr = game.get_map_registry_ref();
  MapPtr depth_map = mr.get_map(depth_map_id);
  
  depth_map->size_ref().set_depth(new_depth);

  auto direction_map = depth_map->get_tile_exits();
  Direction depth_map_dir = DirectionUtils::get_opposite_direction(exit_direction);
  auto exit_it = direction_map.find(depth_map_dir);

  if (exit_it != direction_map.end())
  {
    vector<Coordinate> coords = exit_it->second;

    if (coords.empty())
    {
      ostringstream ss;
      ss << "Generator::update_custom_map_with_current - Tried to link up custom map to random, but exit_direction " << static_cast<int>(exit_direction) << " did not exist.";
      Log::instance().error(ss.str());
    }
    else
    {
      // Iterate over the exits found in the requested direction.  For the
      // first "empty" exit found, link it to the current map.
      for (const auto& coord : coords)
      {
        TilePtr tile = depth_map->at(coord);
        TileExitMap& tile_exit_map = tile->get_tile_exit_map_ref();
        MapExitPtr exit = tile_exit_map.find(depth_map_dir)->second;

        if (!exit->is_using_map_id())
        {
          MapExitUtils::add_exit_to_tile(depth_map, coord, depth_map_dir, linkback_map_id);
          break;
        }
      }
    }
  }
}

vector<string> Generator::get_generator_filters() const
{
  vector<string> no_filters;
  return no_filters;
}

bool Generator::get_ignore_creature_generation_level_checks() const
{
  return false;
}

// Copy any generator properties that need to be a part of the map's
// properties.
void Generator::create_properties_and_copy_to_map(MapPtr map)
{
  vector<string> generator_filters = get_generator_filters();

  if (!generator_filters.empty())
  {
    string generator_filter_csv = String::create_csv_from_string_vector(generator_filters);

    set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_GENERATOR_FILTERS, generator_filter_csv);
  }

  string ignore_lvl_checks_val = get_additional_property(MapProperties::MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS);

  // If there isn't a value defined at the map level, and there usually isn't,
  // then get the generator value.
  if (ignore_lvl_checks_val.empty())
  {
    bool ignore_creature_lvl_checks = get_ignore_creature_generation_level_checks();
    string ignore_creature_lvl_checks_val = Bool::to_string(ignore_creature_lvl_checks);
  }

  set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS, ignore_lvl_checks_val);

  // Set any special feature messages that should be displayed the first time
  // the player enters a level.
  set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS, String::create_csv_from_string_vector(feature_entry_text_sids));
}

void Generator::set_property_to_generator_and_map(MapPtr map, const string& prop, const string& val)
{
  additional_properties[prop] = val;
  map->set_property(prop, val);
}

// Generate roots, berries, etc., on the map, based on the seasons and the
// tiles that are present.
bool Generator::generate_foragables(MapPtr map, const ForagableType ft)
{
  bool generated_foragables = false;

  Game& game = Game::instance();
  WorldPtr world = game.get_current_world();

  if (map && world)
  {
    Calendar& calendar = world->get_calendar();
    ISeasonPtr season = calendar.get_season();

    if (season)
    {
      // Partition the map's tiles based on their type.
      std::map<TileType, vector<TilePtr>> part_tiles = MapUtils::partition_tiles(map);

      // Get the map of tile types to item IDs for the current season.
      std::map<TileType, vector<string>> tile_foragables = get_foragables_for_season(season, ft);

      // For each available item type, generate a number of them and
      // place them randomly.
      for (const auto& forage_pair : tile_foragables)
      {
        TileType tt = forage_pair.first;
        vector<string> items = forage_pair.second;

        auto t_it = part_tiles.find(tt);

        if (t_it != part_tiles.end() && !items.empty())
        {
          vector<TilePtr> avail_tiles = t_it->second;
          size_t t_size = avail_tiles.size();

          if (t_size > 0)
          {
            int num_foragables = RNG::range(FORAGABLE_MIN, FORAGABLE_MAX);
            string item_id = items.at(RNG::range(0, items.size()-1));

            for (int i = 0; i < num_foragables; i++)
            {
              ItemPtr item = ItemManager::create_item(item_id);

              TilePtr rand_tile = avail_tiles.at(RNG::range(0, t_size-1));

              if (rand_tile != nullptr)
              {
                rand_tile->get_items()->add(item);
              }

              item_id = items.at(RNG::range(0, items.size()-1));
            }
          }
        }
      }
    }
  }

  return generated_foragables;
}

map<TileType, vector<string>> Generator::get_foragables_for_season(ISeasonPtr season, const ForagableType ft)
{
  if (season != nullptr)
  {
    if (ft == ForagableType::FORAGABLE_TYPE_HERBS)
    {
      return season->get_herbs();
    }
    else
    {
      return season->get_foragables();
    }
  }

  return {};
}

void Generator::update_depth_details(MapPtr map)
{
  string max_depth_property = get_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH);
  if (!max_depth_property.empty())
  {
    Depth depth = map->size().depth();
    depth.set_maximum(String::to_int(max_depth_property));
    map->size_ref().set_depth(depth);
  }
}