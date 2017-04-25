#include "FloatingTowerGenerator.hpp"
#include "RNG.hpp"

using namespace std;

FloatingTowerGenerator::FloatingTowerGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_AIR)
{
}

MapPtr FloatingTowerGenerator::generate(const Dimensions& dimensions)
{
  MapPtr map = std::make_shared<Map>(dimensions);
 
  fill(map, TileType::TILE_TYPE_AIR);

  pair<Coordinate, Coordinate> tower_boundaries = generate_tower(map);
  place_staircases(map, tower_boundaries);

  return map;
}

pair<Coordinate, Coordinate> FloatingTowerGenerator::generate_tower(MapPtr map)
{
  pair<Coordinate, Coordinate> boundaries({0,0}, {0,0});

  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();

    int width = RNG::range(cols * 0.6, cols * 0.8);
    int height = RNG::range(cols * 0.6, cols * 0.8);

    int start_row = (rows / 2) - (height / 2);
    int start_col = (cols / 2) - (width / 2);
    int end_row = start_row + height;
    int end_col = start_col + width;

    boundaries = {{start_row, start_col}, {end_row, end_col}};
  }

  return boundaries;
}
void FloatingTowerGenerator::place_staircases(MapPtr map, const pair<Coordinate, Coordinate>& tower_boundaries)
{
}

