#include "ForestGenerator.hpp"
#include "SpringsGenerator.hpp"
#include "StreamGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"
#include "Directions.hpp"
#include <vector>

using namespace std;

ForestGenerator::ForestGenerator():
PCT_CHANCE_FOREST_STREAM(50),
PCT_CHANCE_FOREST_SPRINGS(50)
{
}

ForestGenerator::ForestGenerator(const int pct_chance_stream, const int pct_chance_springs)
: PCT_CHANCE_FOREST_STREAM(pct_chance_stream)
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
  MapPtr result_map = MapPtr(new Map(dimensions));

  fill(result_map, TILE_TYPE_TREE);

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
  MapPtr result_map = MapPtr(new Map(*map));

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
        current_tile = TileGenerator::generate(TILE_TYPE_FIELD);
        result_map->insert(row, col, current_tile);
      }
    }
  }

  return result_map;
}

MapPtr ForestGenerator::add_random_stream_or_springs(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));

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
  MapPtr result_map = MapPtr(new Map(*map));

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
  MapPtr result_map = MapPtr(new Map(*map));
  result_map = StreamGenerator::generate(result_map);
  return result_map;
}
