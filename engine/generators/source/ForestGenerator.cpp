#include <vector>
#include "Conversion.hpp"
#include "ForestGenerator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "Directions.hpp"

using namespace std;

ForestGenerator::ForestGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_FOREST)
, PCT_CHANCE_FOREST_STREAM(50)
, PCT_CHANCE_FOREST_SPRINGS(50)
{
}

ForestGenerator::ForestGenerator(const int pct_chance_stream, const int pct_chance_springs)
: Generator("", TileType::TILE_TYPE_FOREST) 
, PCT_CHANCE_FOREST_STREAM(pct_chance_stream)
, PCT_CHANCE_FOREST_SPRINGS(pct_chance_springs)
{
}

MapPtr ForestGenerator::generate()
{
  MapPtr result_map;
  Dimensions default_dimensions;
  result_map = generate(default_dimensions);
  return result_map;
}

MapPtr ForestGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  string world_location_map_key = get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION);
  int world_map_height = String::to_int(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT));
  Coordinate world_location = MapUtils::convert_map_key_to_coordinate(world_location_map_key);
  int pct_chance_shield = fc.calculate_pct_chance_shield(world_map_height, world_location);

  fill(result_map, { {TileType::TILE_TYPE_ROCKY_EARTH, pct_chance_shield}, {TileType::TILE_TYPE_FIELD, 100} });

  if (RNG::percent_chance(80))
  {
    add_random_bushes_and_weeds(result_map, pct_chance_shield);
    GeneratorUtils::potentially_generate_coastline(result_map, this);
  }
  else
  {
    // Rarer: reverse the order and the effect is a shallow coastline
    // with lots of little bushy islands.  This was originally a bug,
    // but it looks good!
    GeneratorUtils::potentially_generate_coastline(result_map, this);
    add_random_bushes_and_weeds(result_map, pct_chance_shield);
  }

  GeneratorUtils::add_random_stream_or_springs(result_map, PCT_CHANCE_FOREST_STREAM, PCT_CHANCE_FOREST_STREAM);

  return result_map;
}

TilePtr ForestGenerator::generate_tile(MapPtr /*current_map*/, int /*row*/, int /*col*/)
{
  TilePtr result_tile;
  return result_tile;
}

void ForestGenerator::add_random_bushes_and_weeds(MapPtr result_map, const int pct_chance_evergreen)
{
  TileGenerator tg;

  string world_location_map_key = get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION);
  int world_map_height = String::to_int(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT));
  Coordinate world_location = MapUtils::convert_map_key_to_coordinate(world_location_map_key);

  Dimensions dim = result_map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr current_tile;

      int shrub = RNG::range(1, 100);

      if (shrub < 3)
      {
        current_tile = tg.generate(TileType::TILE_TYPE_BUSH);
        result_map->insert(row, col, current_tile);
      }
      else if (shrub < 5)
      {
        current_tile = tg.generate(TileType::TILE_TYPE_WEEDS);
        result_map->insert(row, col, current_tile);
      }
      else if (shrub < 50)
      {
        current_tile = generate_tree_based_on_world_location(world_map_height, world_location, pct_chance_evergreen);
        result_map->insert(row, col, current_tile);
      }
    }
  }

  // 20% chance of having a grave or barrow on the map.
  // This makes the map permanent.
  if (RNG::percent_chance(20))
  {
    int gr_row = RNG::range(0, rows-1);
    int gr_col = RNG::range(0, cols-1);

    TilePtr grave_or_barrow = GeneratorUtils::generate_grave_or_barrow();
    result_map->insert(gr_row, gr_col, grave_or_barrow);
    result_map->set_permanent(true);
  }
}

TilePtr ForestGenerator::generate_tree_based_on_world_location(const int /*world_map_height*/, const Coordinate& /*world_coords*/, const int pct_chance_evergreen)
{
  TileGenerator tg;
  TileType tree_type = TileType::TILE_TYPE_TREE;

  // Check to see what type of tile (well, tree tile) should be generated,
  // based on the world map location.  Locations further north/south will have
  // a greater proportion of evergreen trees.
  if (RNG::percent_chance(pct_chance_evergreen))
  {
    tree_type = TileType::TILE_TYPE_EVERGREEN_TREE;
  }  

  TilePtr tile = tg.generate(tree_type);
  return tile;
}

