#include "FloatingTowerGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "RockTile.hpp"

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

  // Ensure that the level isn't diggable.
  // Floating Towers are also outside the view of the divine.
  map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG, to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY, to_string(true));

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
    int height = RNG::range(rows * 0.6, rows * 0.8);

    int start_row = (rows / 2) - (height / 2);
    int start_col = (cols / 2) - (width / 2);
    int end_row = start_row + height;
    int end_col = start_col + width;

    boundaries = {{start_row, start_col}, {end_row, end_col}};

    GeneratorUtils::generate_building(map, start_row, start_col, height, width);
    generate_wall_structure(map, {{start_row+1, start_col+1}, {end_row-1, end_col-1}});
  }

  return boundaries;
}

void FloatingTowerGenerator::place_staircases(MapPtr map, const pair<Coordinate, Coordinate>& tower_boundaries)
{
  if (map != nullptr)
  {
  }
}

// This function uses a turtle-like wall generator.
//
// Starting in the centre of the tower, the turtles (let's say there's four of
// them) move symmetrically to create a pleasing wall pattern.  With each step
// the turtles can move either vertically or horizontally, but not both.
void FloatingTowerGenerator::generate_wall_structure(MapPtr map, const pair<Coordinate, Coordinate>& tower_boundaries)
{
  if (map != nullptr)
  {
    Coordinate top_left = tower_boundaries.first;
    Coordinate bottom_right = tower_boundaries.second;

    int centre_y = (top_left.first + bottom_right.first) / 2;
    int centre_x = (top_left.second + bottom_right.second) / 2;
    int v_steps = 0;
    int h_steps = 0;

    while ((centre_y - v_steps > (top_left.first) + 1) && (centre_x - h_steps > (top_left.second) + 1))
    {
      bool move_vertically = RNG::percent_chance(55);

      if (move_vertically)
      {
        v_steps++;
      }
      else
      {
        h_steps++;
      }

      // Add rock tiles based on the turtle movement.
      TilePtr rock_tile = std::make_shared<RockTile>();
      map->insert({centre_y - v_steps, centre_x - h_steps}, rock_tile);

      rock_tile = std::make_shared<RockTile>();
      map->insert({centre_y - v_steps, centre_x + h_steps}, rock_tile);

      rock_tile = std::make_shared<RockTile>();
      map->insert({centre_y + v_steps, centre_x - h_steps}, rock_tile);

      rock_tile = std::make_shared<RockTile>();
      map->insert({centre_y + v_steps, centre_x + h_steps}, rock_tile);
    }
  }
}
