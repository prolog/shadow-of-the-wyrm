#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "DirectionUtils.hpp"
#include "GeneratorUtils.hpp"
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
#include "TextKeys.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using namespace SOTW;

const int Generator::FORAGABLE_MIN = 0;
const int Generator::FORAGABLE_MAX = 8;
const string Generator::RECURSIVE_PROPERTY_SUFFIX = "_RECURSIVE";
const string Generator::DEPTH_PROPERTY_PREFIX = "_DEPTH_";

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
  map->set_danger(danger_level);
  map->set_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE, get_additional_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE));

  generate_additional_structures(map);

  initialize(map, danger_level);
  create_properties_and_copy_to_map(map);
  map->set_map_type(get_map_type());
    
  return map;
}

void Generator::generate_additional_structures(MapPtr map)
{
  if (map != nullptr)
  {
    if (!get_additional_property(TileTextKeys::TILE_EXTRA_DESCRIPTION_BAZAAR).empty())
    {
      GeneratorUtils::generate_bazaar(map);
    }

    if (!get_additional_property(TileTextKeys::TILE_EXTRA_DESCRIPTION_HERMITAGE).empty())
    {
      GeneratorUtils::generate_hermitage(map);
    }

    if (!get_additional_property(TileTextKeys::TILE_EXTRA_DESCRIPTION_STOREHOUSE).empty())
    {
      GeneratorUtils::generate_storehouses(map);
    }

    if (!get_additional_property(TileTextKeys::TILE_EXTRA_DESCRIPTION_COTTAGE).empty())
    {
      GeneratorUtils::generate_cottage(map);
    }
  }
}

// Initializes essential map properties like terrain type, ID, and permanence.
void Generator::initialize(MapPtr map, const int danger_level)
{
  map->set_terrain_type(map_terrain_type);

  // Make sure this gets set initially so that if another call comes later
  // (e.g., from a different generator in a multi-stage map, like Shrines), 
  // that call can take precedence.
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

    if (std::get<1>(creature_details) == 0 && 
        MapUtils::get_hostile_creatures(CreatureID::CREATURE_ID_PLAYER, map).empty())
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(TextKeys::NO_CREATURES_GENERATED));
      manager.send();
    }
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

pair<bool, bool> Generator::override_depth_update_defaults() const
{
  return make_pair(false, false);
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
    // If the map has not already been made permanent, set the value based
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

map<string, string> Generator::get_recursive_properties() const
{
  map<string, string> rec_props;

  for (const auto& p_pair : additional_properties)
  {
    string rec_prop = p_pair.first;

    if (boost::algorithm::ends_with(rec_prop, RECURSIVE_PROPERTY_SUFFIX))
    {
      rec_prop.erase(rec_prop.find(RECURSIVE_PROPERTY_SUFFIX));

      auto p_it = additional_properties.find(rec_prop);

      // Include both the referant property, as well as the recursive
      // property.
      if (p_it != additional_properties.end())
      {
        rec_props[p_it->first] = p_it->second;
        rec_props[p_pair.first] = p_pair.second;
      }
    }
  }

  return rec_props;
}

map<string, string> Generator::get_depth_properties() const
{
  map<string, string> depth_props;

  for (const auto& prop_pair : additional_properties)
  {
    string p = prop_pair.first;
    string::size_type p_loc = p.find("_");

    if (p_loc != string::npos)
    {
      string numeric_part_s = p.substr(0, p_loc);

      try
      {
        // If we got here, we got a property starting with a number.
        // Remove the numeric part and then check the rest of the
        // property name to see if it's a depth property.
        p.erase(p.find(numeric_part_s), numeric_part_s.size());

        if (boost::starts_with(p, DEPTH_PROPERTY_PREFIX))
        {
          depth_props[prop_pair.first] = prop_pair.second;
        }
      }
      catch (...)
      {
        continue;
      }
    }
  }

  return depth_props;
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

  if (tile == nullptr)
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
    
    // If a creature, feature, or items have been generated on the original 
    // tile, make sure that they make their way to the new one.
    new_staircase_tile->copy_entities(tile);
    new_staircase_tile->set_tile_subtype(tile_subtype);

    // Allow for "infinite dungeons" by setting the permanence flag on the staircases, which will then get copied 
    // to the next generator, which will then set it on the down staircase...
    new_staircase_tile->set_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE, get_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE));

    map->insert(row, col, new_staircase_tile); 

    Depth depth = map->size().depth();

    // Set the depth and original map ID so that these can be copied to all the
    // maps in a particular generation chain.
    new_staircase_tile->set_additional_property(MapProperties::MAP_PROPERTIES_MIN_DEPTH, get_additional_property(MapProperties::MAP_PROPERTIES_MIN_DEPTH));
    new_staircase_tile->set_additional_property(MapProperties::MAP_PROPERTIES_MAX_DEPTH, get_additional_property(MapProperties::MAP_PROPERTIES_MAX_DEPTH));
    new_staircase_tile->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));

    // Ensure that depth increment is copied map to map, as well.
    string depth_incr = get_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);
    if (!depth_incr.empty())
    {
      new_staircase_tile->set_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT, depth_incr);
    }

    // Handle exiting to a previous map in underworld maps like dungeons,
    // mines, crypts, etc.
    // 
    // In these, an up staircase leads to the prev map.
    //
    // For things like floating towers, a down staircase leads to the previous.
    //
    if (does_tile_lead_to_previous_map(get_map_type(), tile_type, depth))
    {
      // This may be empty, in which case, the custom map ID will be empty
      // and terrain will be checked instead, which is the desired behaviour.
      new_staircase_tile->set_custom_map_id(get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID));

      // JCD FIXME: Make this the min depth.
      // If we're on level 1, set the custom map ID to be the original map ID.
      if (std::abs(depth.get_current()) <= 1)
      {
        string original_map_id = get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID);

        // Most of the time this will be set - e.g., via descending from the
        // wilderness.  But maps can also be set within towns, and in that
        // case the original map ID is not set into the generator, and we 
        // need to take care to use the town/etc's map ID instead.
        if (!original_map_id.empty())
        {
          new_staircase_tile->set_custom_map_id(original_map_id);
        }
      }
    }
    else
    {
      // Handle the case where we need to link the new staircase to custom levels.
      set_custom_map_linkage_for_depth(new_staircase_tile, direction, depth, map->get_map_id());
      set_depth_custom_map_id_properties(new_staircase_tile);

      // Copy over any recursive properties as long as we're not linking back
      // to a previous map (only copy recursive properties forwards)
      std::map<string, string> recursive_properties = get_recursive_properties();
      for (const auto& r_pr_pair : recursive_properties)
      {
        new_staircase_tile->set_additional_property(r_pr_pair.first, r_pr_pair.second);
      }

      // Copy forward any depth-specific properties as well
      std::map<string, string> depth_properties = get_depth_properties();
      for (const auto& d_pr_pair : depth_properties)
      {        
        new_staircase_tile->set_additional_property(d_pr_pair.first, d_pr_pair.second);
      }
    }

    add_tile_exit(map, std::make_pair(row, col), direction, link_to_map_exit_id);

    if (set_as_player_default_location)
    {
      map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
    }

    if (tile_type == TileType::TILE_TYPE_UP_STAIRCASE && !map->has_location(MapProperties::MAP_PROPERTIES_DEFAULT_UP_STAIRCASE))
    {
      map->add_or_update_location(MapProperties::MAP_PROPERTIES_DEFAULT_UP_STAIRCASE, {row, col});
    }
    else if (tile_type == TileType::TILE_TYPE_DOWN_STAIRCASE && !map->has_location(MapProperties::MAP_PROPERTIES_DEFAULT_DOWN_STAIRCASE))
    {
      map->add_or_update_location(MapProperties::MAP_PROPERTIES_DEFAULT_DOWN_STAIRCASE, {row, col});
    }

    return true;
  }  
  
  return false;
}

bool Generator::does_tile_lead_to_previous_map(const MapType map_type, const TileType tile_type, const Depth& depth)
{
  if ((map_type == MapType::MAP_TYPE_UNDERWORLD && tile_type == TileType::TILE_TYPE_UP_STAIRCASE) ||
      (map_type == MapType::MAP_TYPE_OVERWORLD && tile_type == TileType::TILE_TYPE_DOWN_STAIRCASE))
  {
    // Wherever we are - under ground, or above - if the depth isn't 0, we
    // should go back to the previous.
    //
    // Disallowing this when depth = 0 ensures that we don't go back to the
    // previous when e.g. going down a staircase in a town, church, etc.
    if (depth.get_current() != 0)
    {
      return true;
    }
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
// for the given tile if the key exists.
void Generator::set_custom_map_linkage_for_depth(TilePtr new_tile, const Direction exit_direction, const Depth& depth, const string& linkback_map_id)
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
    string ignore_creature_lvl_checks_val = std::to_string(ignore_creature_lvl_checks);
  }

  const DeityMap& deity_map = Game::instance().get_deities_cref();
  bool set_def_id = false;

  if (map->get_default_deity_id().empty())
  {
    for (const auto& d_it : deity_map)
    {
      Deity* deity = d_it.second.get();

      if (deity != nullptr)
      {
        vector<string> dg_filters = deity->get_generator_filters();

        for (const auto& gf : generator_filters)
        {
          if (std::find(dg_filters.begin(), dg_filters.end(), gf) != dg_filters.end())
          {
            map->set_default_deity_id(deity->get_id());
            set_def_id = true;
            break;
          }
        }
      }

      if (set_def_id)
      {
        break;
      }
    }
  }

  set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS, ignore_lvl_checks_val);
  
  string dlvl_override = get_additional_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE);
  if (!dlvl_override.empty())
  {
    set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE, dlvl_override);
  }
  
  // The depth properties will be copied to any stairs, allowing them to 
  // propagate.  Any properties that are specific for this depth will be
  // copied to the map.  We can safely call the function at this point
  // because by now, the generator should be done and the depth should
  // be known.
  set_depth_properties_to_map(map);

  // Set any special feature messages that should be displayed the first time
  // the player enters a level.
  set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS, String::create_csv_from_string_vector(feature_entry_text_sids));

  string divine_forbidden = get_additional_property(MapProperties::MAP_PROPERTIES_DIVINE_FORBIDDEN);
  if (!divine_forbidden.empty())
  {
    set_property_to_generator_and_map(map, MapProperties::MAP_PROPERTIES_DIVINE_FORBIDDEN, divine_forbidden);
  }
}

void Generator::set_property_to_generator_and_map(MapPtr map, const string& prop, const string& val)
{
  additional_properties[prop] = val;

  if (map != nullptr)
  {
    map->set_property(prop, val);
  }
}

void Generator::set_depth_properties_to_map(MapPtr map)
{
  if (map != nullptr)
  {
    std::map<string, string> depth_props = get_depth_properties();
    string depth_prefix = std::to_string(map->size().depth().get_current()) + DEPTH_PROPERTY_PREFIX;

    for (const auto& d_pair : depth_props)
    {
      string prop = d_pair.first;

      if (boost::starts_with(prop, depth_prefix))
      {
        prop.erase(prop.find(depth_prefix), depth_prefix.size());
        set_property_to_generator_and_map(map, prop, d_pair.second);
      }
    }
  }
}

// Generate roots, berries, etc., on the map, based on the seasons and the
// tiles that are present.
bool Generator::generate_foragables(MapPtr map, const ForagableType ft)
{
  bool generated_foragables = false;

  Game& game = Game::instance();
  World* world = game.get_current_world();

  if (map && world)
  {
    Calendar& calendar = world->get_calendar();
    ISeason* season = calendar.get_season();

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

map<TileType, vector<string>> Generator::get_foragables_for_season(ISeason* season, const ForagableType ft)
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
  string max_depth_property = get_additional_property(MapProperties::MAP_PROPERTIES_MAX_DEPTH);

  if (!max_depth_property.empty())
  {
    Depth depth = map->size().depth();

    if (max_depth_property == Depth::DEPTH_INFINITE)
    {
      depth.set_has_maximum(false);
    }
    else
    {
      depth.set_maximum(String::to_int(max_depth_property));
    }

    string depth_property = get_additional_property(MapProperties::MAP_PROPERTIES_DEPTH);
    if (!depth_property.empty())
    {
      depth.set_current(String::to_int(depth_property));
    }

    string min_depth_property = get_additional_property(MapProperties::MAP_PROPERTIES_MIN_DEPTH);
    if (!min_depth_property.empty())
    {
      depth.set_minimum(String::to_int(min_depth_property));
    }

    string depth_increment = get_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);
    if (!depth_increment.empty())
    {
      depth.set_increment(String::to_int(depth_increment));
    }

    map->size_ref().set_depth(depth);
  }
}

ExitMovementType Generator::get_last_exit_movement_type() const
{
  ExitMovementType emt = ExitMovementType::EXIT_MOVEMENT_UNDEFINED;
  string emt_s = get_additional_property(MapProperties::MAP_PROPERTIES_EXIT_MOVEMENT_TYPE);

  if (!emt_s.empty())
  {
    emt = static_cast<ExitMovementType>(String::to_int(emt_s));
  }

  return emt;
}

// If a last exit movement type is defined, use that to determine whether to
// place on the down staircase or not.  If this is not defined, fall back on
// the old behaviour of using the depth increment, which made sense six years
// ago but now I have no idea why I did it that way. :(
bool Generator::get_place_on_down_staircase(const ExitMovementType emt) const
{
  bool place_on_down = false;

  if (emt == ExitMovementType::EXIT_MOVEMENT_ASCEND)
  {
    place_on_down = true;
  }
  else if (emt == ExitMovementType::EXIT_MOVEMENT_DESCEND)
  {
    place_on_down = false;
  }
  else if (emt == ExitMovementType::EXIT_MOVEMENT_UNDEFINED)
  {
    string depth_increment = get_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);
    place_on_down = (depth_increment.empty());
  }

  return place_on_down;
}

void Generator::set_feature_entry_text_sids(const vector<string>& new_feature_entry_text_sids)
{
  feature_entry_text_sids = new_feature_entry_text_sids;
}

void Generator::add_feature_entry_text_sid(const std::string& new_sid)
{
  feature_entry_text_sids.push_back(new_sid);
}

void Generator::clear_feature_entry_text_sids()
{
  feature_entry_text_sids.clear();
}
