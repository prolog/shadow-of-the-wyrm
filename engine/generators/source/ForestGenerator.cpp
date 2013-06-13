#include <vector>
#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "ForestGenerator.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "SpringsGenerator.hpp"
#include "StreamGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "Directions.hpp"

using namespace std;

ForestGenerator::ForestGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_FOREST)
, PCT_CHANCE_FOREST_STREAM(50)
, PCT_CHANCE_FOREST_SPRINGS(50)
{
}

ForestGenerator::ForestGenerator(const int pct_chance_stream, const int pct_chance_springs)
: Generator("", TILE_TYPE_FOREST) 
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
  MapPtr result_map = boost::make_shared<Map>(dimensions);

  fill(result_map, TILE_TYPE_FIELD);

  result_map = add_random_bushes_and_weeds (result_map);
//  result_map = apply_conway_rules(result_map);
  result_map = add_random_stream_or_springs(result_map);

  return result_map;
}

TilePtr ForestGenerator::generate_tile(MapPtr current_map, int row, int col)
{
  TilePtr result_tile;
  return result_tile;
}

MapPtr ForestGenerator::add_random_bushes_and_weeds(MapPtr map)
{
  MapPtr result_map = boost::make_shared<Map>(*map);
  string world_location_map_key = get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION);
  int world_map_height = String::to_int(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT));
  Coordinate world_location = MapUtils::convert_map_key_to_coordinate(world_location_map_key);
  int pct_chance_evergreen = fc.calculate_pct_chance_evergreen(world_map_height, world_location);

  Dimensions dim = map->size();
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
        current_tile = TileGenerator::generate(TILE_TYPE_BUSH);
        result_map->insert(row, col, current_tile);
      }
      else if (shrub < 5)
      {
        current_tile = TileGenerator::generate(TILE_TYPE_WEEDS);
        result_map->insert(row, col, current_tile);
      }
      else if (shrub < 50)
      {
        current_tile = generate_tree_based_on_world_location(world_map_height, world_location, pct_chance_evergreen);
        result_map->insert(row, col, current_tile);
      }
    }
  }

  return result_map;
}

TilePtr ForestGenerator::generate_tree_based_on_world_location(const int world_map_height, const Coordinate& world_coords, const int pct_chance_evergreen)
{
  TileType tree_type = TILE_TYPE_TREE;

  // Check to see what type of tile (well, tree tile) should be generated,
  // based on the world map location.  Locations further north/south will have
  // a greater proportion of evergreen trees.
  if (RNG::percent_chance(pct_chance_evergreen))
  {
    tree_type = TILE_TYPE_EVERGREEN_TREE;
  }  

  TilePtr tile = TileGenerator::generate(tree_type);
  return tile;
}

MapPtr ForestGenerator::add_random_stream_or_springs(MapPtr map)
{
  MapPtr result_map = boost::make_shared<Map>(*map);

  int additional_random_feature = RNG::range(1, 100);

  if (additional_random_feature < PCT_CHANCE_FOREST_STREAM)
  {
    result_map = add_random_stream(result_map);
  }
  else
  {
    additional_random_feature = RNG::range(1, 100);

    if (additional_random_feature < PCT_CHANCE_FOREST_SPRINGS)
    {
      result_map = add_random_springs(result_map);
    }
  }

  return result_map;
}

MapPtr ForestGenerator::add_random_springs(MapPtr map)
{
  MapPtr result_map = boost::make_shared<Map>(*map);

  Dimensions dim = result_map->size();
  int springs_size = RNG::dice(3, 2); // min size should be 3.
  int start_y      = RNG::range(1, (dim.get_y() - springs_size - 1));
  int start_x      = RNG::range(1, (dim.get_x() - springs_size - 1));
  int rand_type    = RNG::dice(1, 2);
  SpringsType springs_type = SPRINGS_TYPE_TALL;

  if (rand_type == 2)
  {
    springs_type = SPRINGS_TYPE_WIDE;
  }

  result_map = SpringsGenerator::generate(result_map, start_y, start_x, springs_size, springs_type);

  return result_map;
}

MapPtr ForestGenerator::add_random_stream(MapPtr map)
{
  MapPtr result_map = boost::make_shared<Map>(*map);
  result_map = StreamGenerator::generate(result_map);
  return result_map;
}
