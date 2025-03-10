#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DirectionUtils.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MapProperties.hpp"
#include "MineCalculator.hpp"
#include "MineGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int MineGenerator::MINE_MIN_TRAPS = 0;
const int MineGenerator::MINE_MAX_TRAPS_DIVISOR = 6; 
const int MineGenerator::MINE_MAX_SEGMENTS_MULTIPLIER = 3;

MineGenerator::MineGenerator(const std::string& map_exit_id)
: Generator(map_exit_id, TileType::TILE_TYPE_MINE)
{
}

bool MineGenerator::get_allow_ancient_beasts() const
{
  return true;
}

MapPtr MineGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(dim);

  generate_room(map);
  generate_wall_segments(map);
  generate_traps(map);
  generate_item_piles(map);

  update_depth_details(map);
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

  GeneratorUtils::generate_building(map, 0, 0, rows, cols);
}

void MineGenerator::generate_wall_segments(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int att = 0;
    int max_segment_attempts = dim.get_x() * MINE_MAX_SEGMENTS_MULTIPLIER;

    while (att < max_segment_attempts)
    {
      att++;

      CardinalDirection feature_dir = get_random_direction({ CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST, CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH });
      int seg_y = RNG::range(1, dim.get_y() - 1);
      int seg_x = RNG::range(1, dim.get_x() - 1);

      vector<Coordinate> feature = generate_random_feature(seg_y, seg_x, feature_dir);
      BoundingBox bb = CoordUtils::get_new_bounding_box(CoordUtils::get_minimum_bounding_box(dim, feature, 1), DirectionUtils::to_direction(feature_dir));
      bool tiles_ok = MapUtils::tiles_in_range_match_type(map, bb, TileType::TILE_TYPE_DUNGEON);

      if (tiles_ok)
      {
        generate_rock_feature(map, feature);
      }
    }
  }
}

void MineGenerator::generate_rock_feature(MapPtr map, const vector<Coordinate>& feature)
{
  TileGenerator tg;

  for (const Coordinate& fc : feature)
  {
    TilePtr tile = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(fc, tile);
  }
}

vector<Coordinate> MineGenerator::generate_random_feature(const int y, const int x, const CardinalDirection cd)
{
  vector<Coordinate> feature_coords;
  int feat_type = RNG::range(1, 4);
  Coordinate start = {y, x};

  if (feat_type == 1)
  {
    feature_coords = CoordUtils::get_t_coordinates(start, cd, RNG::range(1, 3));
  }
  else if (feat_type == 2)
  {
    feature_coords = CoordUtils::get_cross(start, RNG::range(1, 2));
  }
  else if (feat_type == 3)
  {
    feature_coords = CoordUtils::get_line_segment(start, DirectionUtils::to_direction(cd), RNG::range(2, 4));
  }
  else
  {
    vector<CardinalDirection> potential_dirs = DirectionUtils::get_perpendicular_directions(cd);
    vector<CardinalDirection> step_dirs = {cd, potential_dirs.at(RNG::range(0, potential_dirs.size() - 1))};

    if (!potential_dirs.empty())
    {
      feature_coords = CoordUtils::get_stepped_coordinates(start, step_dirs, RNG::range(1,3));
    }
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
  bool place_player_on_down_staircase = get_place_on_down_staircase(get_last_exit_movement_type());

  if (map != nullptr)
  {
    // Place down staircase.
    if (depth.has_more_levels(Direction::DIRECTION_DOWN))
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
  string danger_level_override = get_additional_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE);
  if (!danger_level_override.empty() && String::to_int(danger_level_override) <= 0)
  {
    return;
  }

  int max_traps = map->size().get_x() / MINE_MAX_TRAPS_DIVISOR;
  int num_traps = RNG::range(MINE_MIN_TRAPS, max_traps);
  GeneratorUtils::generate_traps(map, num_traps);
}

void MineGenerator::generate_item_piles(MapPtr map)
{
  vector<std::string> item_ids = { ItemIdKeys::ITEM_ID_ROCK, ItemIdKeys::ITEM_ID_STONE, ItemIdKeys::ITEM_ID_HUGE_ROCK, ItemIdKeys::ITEM_ID_STONE_BLOCK };
  vector<std::string> rarer_items = { ItemIdKeys::ITEM_ID_COAL, ItemIdKeys::ITEM_ID_STEEL_INGOT, ItemIdKeys::ITEM_ID_IRON_INGOT };

  for (const string& ri : rarer_items)
  {
    if (RNG::percent_chance(50))
    {
      item_ids.push_back(ri);
    }
  }

  Dimensions dim = map->size();

  for (const string& id : item_ids)
  {
    int num_items = RNG::range(2, 4);
    for (int i = 0; i < num_items; i++)
    {
      for (int j = 0; j < 50; j++)
      {
        int sh_y = RNG::range(0, dim.get_y() - 1);
        int sh_x = RNG::range(0, dim.get_x() - 1);

        TilePtr tile = map->at(sh_y, sh_x);

        if (tile != nullptr && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
        {
          ItemPtr shard = ItemManager::create_item(id, num_items);
          tile->get_items()->merge_or_add(shard, InventoryAdditionType::INVENTORY_ADDITION_FRONT);

          break;
        }
      }
    }
  }

  generate_magici_shards(map);
}

void MineGenerator::generate_magici_shards(MapPtr map)
{
  if (map != nullptr)
  {
    MineCalculator mc;

    if (RNG::percent_chance(mc.calculate_pct_chance_magici_shards(danger_level)))
    {
      Dimensions dim = map->size();
      int num_shards = RNG::range(3, 6);

      for (int i = 0; i < 50; i++)
      {
        int sh_y = RNG::range(0, dim.get_y() - 1);
        int sh_x = RNG::range(0, dim.get_x() - 1);

        TilePtr tile = map->at(sh_y, sh_x);

        if (tile != nullptr && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
        {
          ItemPtr shard = ItemManager::create_item(ItemIdKeys::ITEM_ID_MAGICI_SHARD, num_shards);
          tile->get_items()->merge_or_add(shard, InventoryAdditionType::INVENTORY_ADDITION_FRONT);

          break;
        }
      }
    }
  }
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