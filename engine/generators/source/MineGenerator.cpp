#include "CoordUtils.hpp"
#include "DirectionUtils.hpp"
#include "GeneratorUtils.hpp"
#include "MineGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int MineGenerator::MINE_MIN_TRAPS = 0;
const int MineGenerator::MINE_MAX_TRAPS = 12;
const int MineGenerator::MIN_EW_SEGMENTS = 1;
const int MineGenerator::MIN_NS_SEGMENTS = 1;
const int MineGenerator::MAX_EW_DIVISOR = 15;
const int MineGenerator::MAX_NS_DIVISOR = 4;
const int MineGenerator::MAX_SEGMENT_ATTEMPTS = 100;
const int MineGenerator::MIN_SEGMENT_WIDTH = 3;
const int MineGenerator::MAX_SEGMENT_WIDTH = 7;
const int MineGenerator::MIN_SEGMENT_HEIGHT = 3;
const int MineGenerator::MAX_SEGMENT_HEIGHT = 5;

MineGenerator::MineGenerator(const std::string& map_exit_id)
: Generator(map_exit_id, TileType::TILE_TYPE_MINE)
{
}

MapPtr MineGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(dim);

  generate_room(map);
  generate_wall_segments(map);
  generate_traps(map);
  place_staircases(map);

  return map;
}

MapType MineGenerator::get_map_type() const
{
  return MapType::MAP_TYPE_UNDERWORLD;
}

void MineGenerator::generate_room(MapPtr map)
{
  TileGenerator tg;
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  GeneratorUtils::generate_building(map, 1, 1, rows - 3, cols - 3);
}

void MineGenerator::generate_wall_segments(MapPtr map)
{
  generate_ew_wall_segments(map);
  generate_ns_wall_segments(map);
}

void MineGenerator::generate_ew_wall_segments(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int num_segments = RNG::range(MIN_EW_SEGMENTS, dim.get_x() / MAX_EW_DIVISOR);
    int att = 0;

    while (att < MAX_SEGMENT_ATTEMPTS)
    {
      att++;

      CardinalDirection wall_dir = get_random_direction({CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST});
      int wall_y = RNG::range(2, dim.get_y()-3);
      int wall_x = wall_dir == CardinalDirection::CARDINAL_DIRECTION_WEST ? 1 : dim.get_x() - 2;

      vector<Coordinate> feature = generate_random_feature(wall_y, wall_x, wall_dir);
      Direction shift_dir = DirectionUtils::get_opposite_direction(DirectionUtils::to_direction(wall_dir));
      BoundingBox bb = CoordUtils::get_new_bounding_box(CoordUtils::get_minimum_bounding_box(dim, feature, 1), shift_dir);
    }
  }
}

void MineGenerator::generate_ns_wall_segments(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int num_segments = RNG::range(MIN_NS_SEGMENTS, dim.get_y() / MAX_NS_DIVISOR);
    int att = 0;

    while (att < MAX_SEGMENT_ATTEMPTS)
    {
      att++;

      CardinalDirection wall_dir = get_random_direction({CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH});
      int wall_x = RNG::range(2, dim.get_x()-3);
      int wall_y = wall_dir == CardinalDirection::CARDINAL_DIRECTION_NORTH ? 1 : dim.get_y() - 2;

      vector<Coordinate> feature = generate_random_feature(wall_y, wall_x, wall_dir);
      Direction shift_dir = DirectionUtils::get_opposite_direction(DirectionUtils::to_direction(wall_dir));
      BoundingBox bb = CoordUtils::get_new_bounding_box(CoordUtils::get_minimum_bounding_box(dim, feature, 1), shift_dir);
    }
  }
}

vector<Coordinate> MineGenerator::generate_random_feature(const int y, const int x, const CardinalDirection cd)
{
  vector<Coordinate> feature_coords;
  int feat_type = RNG::range(1, 3);
  Coordinate start = {y, x};

  if (feat_type == 1)
  {
    feature_coords = CoordUtils::get_beam_coordinates(start, DirectionUtils::to_direction(cd), RNG::range(2, 5));
  }
  else if (feat_type == 2)
  {
    feature_coords = CoordUtils::get_t_coordinates(start, cd, RNG::range(1, 3));
  }
  else
  {
    feature_coords = CoordUtils::get_stepped_coordinates(start, {}, 2);
  }

  return feature_coords;
}

// Place the stairs randomly.
void MineGenerator::place_staircases(MapPtr map)
{
  Dimensions dim = map->size();
  Depth depth = dim.depth();

  int min_y = 1;
  int max_y = dim.get_y() - 2;
  int min_x = 1;
  int max_x = dim.get_x() - 2;

  int y, x;
  bool found = false;
  string depth_increment = get_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);
  bool place_player_on_down_staircase = (depth_increment.empty());

  if (map != nullptr)
  {
    // Place down staircase.
    if (depth.get_current() < depth.get_maximum())
    {
      while (!found)
      {
        y = RNG::range(min_y, max_y);
        x = RNG::range(min_x, max_x);

        TilePtr tile = map->at(y, x);

        found = place_down_staircase(map, y, x, TileType::TILE_TYPE_MINE, Direction::DIRECTION_DOWN, false, place_player_on_down_staircase);
      }
    }

    found = false;

    // Place up staircase.
    while (!found)
    {
      y = RNG::range(min_y, max_y);
      x = RNG::range(min_x, max_x);

      found = place_up_staircase(map, y, x, TileType::TILE_TYPE_MINE, Direction::DIRECTION_UP, get_permanence(), !place_player_on_down_staircase);
    }
  }
}

// By default, persist any generated mines.
bool MineGenerator::get_permanence_default() const
{
  return true;
}

// Generate a few traps throughout the mines.
void MineGenerator::generate_traps(MapPtr map)
{
  int num_traps = RNG::range(MINE_MIN_TRAPS, MINE_MAX_TRAPS);
  GeneratorUtils::generate_traps(map, num_traps);
}

CardinalDirection MineGenerator::get_random_direction(const vector<CardinalDirection>& cd)
{
  CardinalDirection dir = CardinalDirection::CARDINAL_DIRECTION_NULL;

  if (!cd.empty())
  {
    dir = cd[RNG::range(0, cd.size()-1)];
  }

  return dir;
}