#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreationUtils.hpp"
#include "ItemGenerationManager.hpp"
#include "TileGenerator.hpp"
#include "Game.hpp"
#include "Generator.hpp"
#include "Map.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

Generator::Generator(const string& new_map_exit_id, const TileType new_map_terrain_type)
: map_exit_id(new_map_exit_id), map_terrain_type(new_map_terrain_type)
{
}

// Always calls the version with both a danger_level and dimensions, so that
// everything is set up properly.
MapPtr Generator::generate_and_initialize(const uint danger_level)
{
  Dimensions dim;
  return generate_and_initialize(danger_level, dim);
}

MapPtr Generator::generate_and_initialize(const uint danger_level, const Dimensions& dim)
{
  Dimensions new_dim = update_dimensions_if_necessary(dim, get_map_type(), danger_level);
  MapPtr map = generate(new_dim);
  initialize(map, danger_level);
  
  return map;
}

// JCD FIXME: Right now this only handles positive depth (underground).
// Extend this later to handle negative depth (multiple floors, etc.)
Dimensions Generator::update_dimensions_if_necessary(const Dimensions& dim, const MapType map_type, const uint danger_level)
{
  Dimensions d = dim;

  // This is theoretically dangerous.
  //
  // However, since danger level will be more of a byte than an int, 
  // I think I can sleep at night.
  const int signed_danger_level = static_cast<int>(danger_level);

  if (map_type == MAP_TYPE_UNDERWORLD)
  {
    if (signed_danger_level > d.depth().get_maximum())
    {
      Depth depth(signed_danger_level, signed_danger_level);
      d.set_depth(depth);
    }
  }

  return d;
}

void Generator::initialize(MapPtr map, const uint danger_level)
{
  map->set_terrain_type(map_terrain_type);
  generate_creatures(map, danger_level);
  generate_initial_items(map, danger_level);

  boost::uuids::uuid id = boost::uuids::random_generator()();
  map->set_map_id(Uuid::to_string(id));
  set_map_permanence(map);
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
  Dimensions dim = map->size();

  int rows = dim.get_y();
  int cols = dim.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr current_tile = TileGenerator::generate(tile_type);
      map->insert(row, col, current_tile);
    }
  }
}

// Generate the creatures.  Returns true if creatures were created, false otherwise.
bool Generator::generate_creatures(MapPtr map, const uint danger_level)
{
  bool creatures_generated = false;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  CreatureGenerationManager cgm;

  Rarity rarity = CreationUtils::generate_rarity();

  Game* game = Game::instance();
  
  if (game)
  {
    ActionManager am = game->get_action_manager_ref();
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
  }

  return creatures_generated;
}

bool Generator::update_creatures(MapPtr map, const uint danger_level)
{
  return false;
}

// Seed the initial items.  Returns true if the items were created, false otherwise.
// By default, no initial items are generated.  This function should be overridden
// for generators where this is expected (dungeons, maybe villages, etc).
bool Generator::generate_initial_items(MapPtr map, const uint danger_level)
{
  return false;
}

bool Generator::update_items(MapPtr map, const uint danger_level)
{
  return false;
}

void Generator::set_map_permanence(MapPtr map)
{
  if (map)
  {
    map->set_permanent(get_permanence_default());
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

// Maps are not permanent by default.  For certain map types (fields, forests, etc),
// this is okay.  For others (dungeons, graveyards - really, anything readily
// exploitable), permanence will need to be set.
bool Generator::get_permanence_default() const
{
  return false;
}