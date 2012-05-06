#include "CreatureGenerationManager.hpp"
#include "ItemGenerationManager.hpp"
#include "TileGenerator.hpp"
#include "Generator.hpp"
#include "Map.hpp"

using namespace std;

Generator::Generator(const string& new_map_exit_id, const TileType new_map_terrain_type)
: map_exit_id(new_map_exit_id), map_terrain_type(new_map_terrain_type)
{
}

MapPtr Generator::generate_and_initialize()
{
  MapPtr map = generate();
  initialize(map);

  return map;
}

MapPtr Generator::generate_and_initialize(const Dimensions& dim)
{
  MapPtr map = generate(dim);
  initialize(map);
  
  return map;
}

void Generator::initialize(MapPtr map)
{
  map->set_terrain_type(map_terrain_type);
  generate_creatures(map);
  generate_initial_items(map);
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
bool Generator::generate_creatures(MapPtr map)
{
  CreatureGenerationManager cgm;
  return false;
}

bool Generator::update_creatures(MapPtr map)
{
  CreatureGenerationManager cgm;
  return false;
}

// Seed the initial items.  Returns true if the items were created, false otherwise.
// By default, no initial items are generated.  This function should be overridden
// for generators where this is expected (dungeons, maybe villages, etc).
bool Generator::generate_initial_items(MapPtr map)
{
  ItemGenerationManager igm;
  return false;
}

bool Generator::update_items(MapPtr map)
{
  ItemGenerationManager igm;
  return false;
}
