#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CreationUtils.hpp"
#include "DirectionUtils.hpp"
#include "Log.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapExitUtils.hpp"
#include "MapProperties.hpp"
#include "ItemGenerationManager.hpp"
#include "TileGenerator.hpp"
#include "Game.hpp"
#include "Generator.hpp"
#include "Map.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using namespace SL;

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
  if (create_creatures)
  {
    MapCreatureGenerator mcg;
    mcg.generate_creatures(map, danger_level, additional_properties);
  }

  if (create_items && can_create_initial_items())
  {
    generate_initial_items(map, danger_level);
  }
}

MapPtr Generator::generate()
{
  Dimensions default_dimensions;
  MapPtr result_map = generate(default_dimensions);

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
bool Generator::generate_initial_items(MapPtr map, const int danger_level)
{
  bool items_generated = false;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  ItemGenerationManager igm;

  Rarity rarity = CreationUtils::generate_rarity();

  Game& game = Game::instance();
  
  ActionManager am = game.get_action_manager_ref();
  uint num_items_to_place = RNG::range(1, CreationUtils::random_maximum_items(dim.get_y(), dim.get_x()));
  uint current_items_placed = 0;
  uint unsuccessful_attempts = 0;

  // Generate the vector of possible items for this map.
  ItemGenerationVec generation_vec = igm.generate_item_generation_vec(1, danger_level, rarity);

  while ((current_items_placed < num_items_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_ITEM_ATTEMPTS))
  {
    int enchant_points = RNG::range(0, (danger_level / 2));
    ItemPtr generated_item = igm.generate_item(am, generation_vec, enchant_points);

    bool placed_item = false;

    if (generated_item)
    {
      while (!placed_item)
      {
        int item_row = RNG::range(0, rows-1);
        int item_col = RNG::range(0, cols-1);
      
        // Check to see if the tile isn't blocking
        TilePtr tile = map->at(item_row, item_col);

        if (MapUtils::is_tile_available_for_item(tile))
        {
          tile->get_items()->add(generated_item);

          if (!items_generated) items_generated = true;
          current_items_placed++;
          placed_item = true;
        }
        else
        {
          unsuccessful_attempts++;
        }
      }
    }
    else
    {
      unsuccessful_attempts++;
    }
  }

  return items_generated;
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
    map->set_permanent(get_permanence_default());
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

bool Generator::place_staircase(MapPtr map, const int row, const int col, const TileType tile_type, const TileType tile_subtype, const Direction direction, const bool link_to_map_exit_id, const bool set_as_player_default_location)
{
  TileGenerator tg;
  TilePtr tile = map->at(row, col);
  
  if (tile)
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
    }

    add_tile_exit(map, std::make_pair(row, col), direction, link_to_map_exit_id);

    if (set_as_player_default_location)
    {
      map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
    }
  }  
  
  return true;
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