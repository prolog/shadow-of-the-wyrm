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
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  CreatureGenerationManager cgm;

  Rarity rarity = CreationUtils::generate_rarity();

  Game* game = Game::instance();
  
  if (game)
  {
    ActionManager am = game->get_action_manager_ref();
    
    CreaturePtr generated_creature = cgm.generate_creature(am, map_terrain_type, danger_level, rarity);
    
    if (generated_creature)
    {
      int creature_row = RNG::range(0, rows-1);
      int creature_col = RNG::range(0, cols-1);
      
      // Check to see if the spot is empty, and if a creature can be added there.
      TilePtr tile = map->at(creature_row, creature_col);

      if (MapUtils::is_tile_available_for_creature(tile))
      {
        Coordinate coords(creature_row, creature_col);
        tile->set_creature(generated_creature);
        map->add_or_update_location(generated_creature->get_id(), coords);
      }
    }
  }

  return true;
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

// By default, overworld.  Override as necessary.
MapType Generator::get_map_type() const
{
  return MAP_TYPE_OVERWORLD;
}
