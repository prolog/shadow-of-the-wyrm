#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreationUtils.hpp"
#include "CreatureFactory.hpp"
#include "Log.hpp"
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
: map_exit_id(new_map_exit_id), map_terrain_type(new_map_terrain_type)
{
}

// Always calls the version with both a danger_level and dimensions, so that
// everything is set up properly.
MapPtr Generator::generate_and_initialize(const int danger_level)
{
  Dimensions dim;
  return generate_and_initialize(danger_level, dim);
}

MapPtr Generator::generate_and_initialize(const int danger_level, const Depth& depth)
{
  Dimensions dim;
  dim.set_depth(depth);

  return generate_and_initialize(danger_level, dim);
}

MapPtr Generator::generate_and_initialize(const int danger_level, const Dimensions& dim)
{
  MapPtr map = generate(dim);
  initialize(map, danger_level);
  
  return map;
}

// Initializes essential map properties like terrain type, ID, and permanence.
void Generator::initialize(MapPtr map, const int danger_level)
{
  map->set_terrain_type(map_terrain_type);

  boost::uuids::uuid id = boost::uuids::random_generator()();
  map->set_map_id(Uuid::to_string(id));
  set_map_permanence(map);
}

// Creates the initial set of entities (creatures and items) present
// on the map.
void Generator::create_entities(MapPtr map, const int danger_level, const bool create_creatures, const bool create_items)
{
  if (create_creatures)
  {
    generate_creatures(map, danger_level);
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

// Generate the creatures.  Returns true if creatures were created, false otherwise.
bool Generator::generate_creatures(MapPtr map, const int danger_level)
{
  bool creatures_generated = false;

  if (has_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES))
  {
    return generate_initial_set_creatures(map);
  }
  else
  {
    return generate_random_creatures(map, danger_level);
  }
}

bool Generator::generate_initial_set_creatures(MapPtr map)
{
  bool creatures_generated = false;

  string initial_creatures = get_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
  vector<string> creature_ids = String::create_string_vector_from_csv_string(initial_creatures);

  try
  {
    for (const string& creature_id : creature_ids)
    {
      creatures_generated = MapUtils::place_creature_randomly(map, creature_id);
    }
  }
  catch(...)
  {
    Log::instance().error("Attempted to generate initial set creatures, but vector could not be deserialized (this is really bad).");
  }

  return creatures_generated;
}

bool Generator::generate_random_creatures(MapPtr map, const int danger_level)
{
  bool creatures_generated = false;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  CreatureGenerationManager cgm;

  Rarity rarity = CreationUtils::generate_rarity();

  Game& game = Game::instance();
  
  ActionManager am = game.get_action_manager_ref();
  uint num_creatures_to_place = RNG::range(1, CreationUtils::random_maximum_creatures(dim.get_y(), dim.get_x()));
  uint current_creatures_placed = 0;
  uint unsuccessful_attempts = 0;

  // Generate the list of possible creatures for this map.
  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(map_terrain_type, danger_level, rarity);

  while ((current_creatures_placed < num_creatures_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS))
  {
    CreaturePtr generated_creature = cgm.generate_creature(am, generation_map);
    
    if (generated_creature)
    {
      int creature_row = RNG::range(0, rows-1);
      int creature_col = RNG::range(0, cols-1);
      
      // Check to see if the spot is empty, and if a creature can be added there.
      TilePtr tile = map->at(creature_row, creature_col);

      if (MapUtils::is_tile_available_for_creature(generated_creature, tile))
      {
        Coordinate coords(creature_row, creature_col);
        MapUtils::add_or_update_location(map, generated_creature, coords);
        if (!creatures_generated) creatures_generated = true;
        current_creatures_placed++;
      }
      else
      {
        unsuccessful_attempts++;
      }
    }
    else
    {
      unsuccessful_attempts++;
    }
  }

  return creatures_generated;
}

bool Generator::update_creatures(MapPtr map, const int danger_level)
{
  // JCD FIXME
  return false;
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
  ItemGenerationVec generation_vec = igm.generate_item_generation_vec(danger_level, rarity);

  while ((current_items_placed < num_items_to_place) && (unsuccessful_attempts < CreationUtils::MAX_UNSUCCESSFUL_ITEM_ATTEMPTS))
  {
    ItemPtr generated_item = igm.generate_item(am, generation_vec);

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
          tile->get_items().add(generated_item);

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
  return MAP_TYPE_OVERWORLD;
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

bool Generator::place_staircase(MapPtr map, const int row, const int col, const TileType tile_type, const TileType tile_subtype, const Direction direction, bool link_to_map_exit_id, bool set_as_player_default_location)
{
  TileGenerator tg;
  TilePtr tile = map->at(row, col);
  
  if (tile)
  {
    Coordinate c(row, col);
    
    TilePtr new_staircase_tile = tg.generate(tile_type);
    new_staircase_tile->set_tile_subtype(tile_subtype);

    if (link_to_map_exit_id)
    {
      if (!map_exit_id.empty())
      {
        MapExitUtils::add_exit_to_tile(new_staircase_tile, direction, map_exit_id);
      }      
    }
    // Otherwise, if we're not linking to a map exit ID, we should map to a tile exit.
    else
    {
      MapExitUtils::add_exit_to_tile(new_staircase_tile, direction, tile_subtype);
    }

    // Allow for "infinite dungeons" by setting the permanence flag on the staircases, which will then get copied 
    // to the next generator, which will then set it on the down staircase...
    new_staircase_tile->set_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE, get_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE));

    map->insert(row, col, new_staircase_tile); 

    // Handle exiting to a previous map in underworld maps like dungeons,
    // mines, crypts, etc.
    if (get_map_type() == MAP_TYPE_UNDERWORLD && tile_type == TILE_TYPE_UP_STAIRCASE)
    {
      Depth depth = map->size().depth();

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

    if (set_as_player_default_location)
    {
      map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
    }
  }  
  
  return true;
}
