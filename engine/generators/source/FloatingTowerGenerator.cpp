#include <sstream>
#include "FloatingTowerGenerator.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "GeneratorUtils.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "RockTile.hpp"

using namespace std;

FloatingTowerGenerator::FloatingTowerGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_FLOATING_TOWER)
{
}

MapPtr FloatingTowerGenerator::generate(const Dimensions& dimensions)
{
  MapPtr map = std::make_shared<Map>(dimensions);
 
  fill(map, TileType::TILE_TYPE_AIR);

  pair<Coordinate, Coordinate> tower_boundaries = generate_tower(map);
  stringstream ss;

  // Ensure the tower wall is not included in the generation coords.
  ss << tower_boundaries.first.first+1 << "," << tower_boundaries.first.second+1 << "," << tower_boundaries.second.first-1 << "," << tower_boundaries.second.second-1;
  map->set_property(MapProperties::MAP_PROPERTIES_GENERATION_COORDINATES, ss.str());

  place_staircases(map, tower_boundaries);

  // Ensure that the level isn't diggable.
  // Floating Towers are also outside the view of the divine.
  // Teleporting is also not allowed, as it makes clearing creatures trivially
  // easy, by sending them to their deaths.
  map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG, to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY, to_string(true));
  map->set_property(MapProperties::MAP_PROPERTIES_CANNOT_TELEPORT, to_string(true));

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

    int height = RNG::range(rows * 0.6, rows * 0.8);
    if (height % 2 == 0) height++;
    int width = 2 * height + 1;

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
    bool place_player_on_up_staircase = (get_place_on_down_staircase(get_last_exit_movement_type()) == false);
    
    // To find the staircase locations, start at the centre of the tower.
    // Increment outward, step by step, until at least 2 possible tiles
    // are open.
    Coordinate centre = CoordUtils::get_centre_coordinate(tower_boundaries.first, tower_boundaries.second);
    vector<Coordinate> potential_stair_locations = get_stair_locations(map, centre, tower_boundaries);
    std::shuffle(potential_stair_locations.begin(), potential_stair_locations.end(), RNG::get_engine());

    update_depth_details(map);
    Depth depth = map->size().depth();

    // Define an up staircase if we aren't as high up as we can go.
    // ie, as long as current depth > min depth.
    if (depth.get_current() > depth.get_minimum())
    {
      Coordinate up_stairs = potential_stair_locations.back();
      potential_stair_locations.pop_back();

      place_up_staircase(map, up_stairs.first, up_stairs.second, TileType::TILE_TYPE_FLOATING_TOWER, Direction::DIRECTION_UP, false, place_player_on_up_staircase);
    }

    // Always place a down staircase in a floating tower (since we start at the
    // base and make our way up).
    Coordinate down_stairs = potential_stair_locations.back();
    potential_stair_locations.pop_back();

    place_down_staircase(map, down_stairs.first, down_stairs.second, TileType::TILE_TYPE_FLOATING_TOWER, Direction::DIRECTION_DOWN, false, !place_player_on_up_staircase);
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
    Coordinate centre = CoordUtils::get_centre_coordinate(top_left, bottom_right);

    int centre_y = centre.first;
    int centre_x = centre.second;
    int v_steps = 0;
    int h_steps = 0;

    // First, place solid rock at the very centre.
    TilePtr rock_tile = std::make_shared<RockTile>();
    map->insert({centre_y, centre_x}, rock_tile);

    // Next, create a geometric-y pattern using turtle movement.
    while ((centre_y - v_steps > (top_left.first) + 1) && (centre_x - h_steps > (top_left.second) + 1))
    {
      // The probability is tilted more towards horizontal because there are
      // more horizontal tiles and the resulting shape looks better.
      bool move_vertically = RNG::percent_chance(38);

      if (move_vertically)
      {
        v_steps++;
      }
      else
      {
        h_steps++;
      }

      // Add rock tiles based on the turtle movement.
      rock_tile = std::make_shared<RockTile>();
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

vector<Coordinate> FloatingTowerGenerator::get_stair_locations(MapPtr map, const Coordinate& centre, const pair<Coordinate, Coordinate>& tower_boundaries)
{
  vector<Coordinate> stair_locs;

  // Find some potential stair locations.  Once we have enough to create some
  // variance (but still remain close to the centre of the map), break out of
  // the loop.
  for (int offset = 0; centre.first - offset > tower_boundaries.first.first && centre.second - offset > tower_boundaries.first.second; offset++)
  {
    vector<Coordinate> coords = { { centre.first - offset, centre.second - offset },
    { centre.first - offset, centre.second + offset },
    { centre.first + offset, centre.second - offset },
    { centre.first + offset, centre.second + offset } };

    for (const Coordinate& c : coords)
    {
      TilePtr tile = map->at(c);

      if (tile && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
      {
        stair_locs.push_back(c);
      }
    }

    if (stair_locs.size() > 8)
    {
      break;
    }
  }

  return stair_locs;
}

bool FloatingTowerGenerator::get_permanence_default() const
{
  return true;
}

pair<bool, bool> FloatingTowerGenerator::override_depth_update_defaults() const
{
  return make_pair(true, true);
}