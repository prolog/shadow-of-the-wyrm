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

    generate_wall_structure(map, boundaries);
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

      // JCD TODO: Turtle stuff I have not yet implemented.
      // No, you're procrastinating.

      if (move_vertically)
      {
        v_steps++;
      }
      else
      {
        h_steps++;
      }
    }

  }
}
