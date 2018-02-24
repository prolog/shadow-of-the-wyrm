#include "PublicAreaSectorFeatureGenerator.hpp"
#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "ShopGenerator.hpp"
#include "StatueGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int PublicAreaSectorFeatureGenerator::MIN_PLAZA_FOUNTAIN_HEIGHT = 5;
const int PublicAreaSectorFeatureGenerator::MIN_PLAZA_FOUNTAIN_WIDTH = 5;

PublicAreaSectorFeatureGenerator::PublicAreaSectorFeatureGenerator()
: features({{100, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PLAZA},
            {101, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_SHOP},
            {102, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK}})
{
}

bool PublicAreaSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx)
{
  bool created = false;
  PublicSectorFeatureType feat = get_random_feature(feat_idx);

  switch (feat)
  {
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PLAZA:
      created = generate_plaza(map, start_coord, end_coord);
      break;
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_SHOP:
      created = generate_shop(map, start_coord, end_coord);
      break;
    case PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK:
    default:
      created = generate_park(map, start_coord, end_coord);
      break;
  }

  return created;
}

bool PublicAreaSectorFeatureGenerator::generate_park(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  Coordinate park_end_coord = end_coord;
  int height = CoordUtils::get_height(start_coord, end_coord);
  int width = CoordUtils::get_width(start_coord, end_coord);

  bool generate_benches = RNG::percent_chance(50);
  bool generate_statue_perimeter = RNG::percent_chance(75);
  bool generate_pond = !generate_statue_perimeter || RNG::percent_chance(75);

  if (map != nullptr)
  {
    TileGenerator tg;
    TilePtr tile;
    int row_cnt = 1;

    for (int row = start_coord.first; row <= end_coord.first; row++)
    {
      int col_cnt = 1;

      for (int col = start_coord.second; col <= end_coord.second; col++)
      {
        tile = nullptr;

        if (generate_statue_perimeter && 
            should_generate_perimeter_statue(row, col, start_coord, end_coord, row_cnt, col_cnt))
        {
          // Add a statue to the existing tile.
          DecorativeStatueType dst = static_cast<DecorativeStatueType>(RNG::range(static_cast<int>(DecorativeStatueType::DECORATIVE_STATUE_TYPE_FIRST), static_cast<int>(DecorativeStatueType::DECORATIVE_STATUE_TYPE_LAST)));
          FeaturePtr statue = StatueGenerator::generate_decorative_statue(dst);

          if (statue != nullptr)
          {
            tile = map->at(row, col);

            if (tile && !tile->has_feature())
            {
              tile->set_feature(statue);
            }
          }
        }
        else if (row > start_coord.first && row < end_coord.first && col > start_coord.second && col < end_coord.second)
        {
          if (RNG::percent_chance(10))
          {
          tile = tg.generate(TileType::TILE_TYPE_FRUIT_TREE);
          }
          else if (RNG::percent_chance(15))
          {
            tile = tg.generate(TileType::TILE_TYPE_TREE);
          }
        }

        if (tile != nullptr)
        {
          map->insert({ row, col }, tile);
        }

        // For now, just to test things, set everything to fruit trees.
        if (!generated)
        {
          generated = true;
        }

        col_cnt++;
      }

      row_cnt++;
    }

    if (generate_pond)
    {
      int pond_height = (height / (height / 2));
      int pond_width = RNG::range(width / 6, width / 2);

      for (int row = start_coord.first + (height / 2) - (pond_height / 2); row <= start_coord.first + (height / 2) + (pond_height / 2); row++)
      {
        for (int col = start_coord.second + (width / 2) - (pond_width / 2); col <= start_coord.second + (width / 2) + (pond_width / 2); col++)
        {
          TilePtr tile = tg.generate(TileType::TILE_TYPE_SPRINGS);
          map->insert({ row, col }, tile);
        }
      }
    }

    if (generate_benches)
    {
      int num_benches = RNG::range(2, 5);
      int num_placed = 0;

      for (int i = 0; i < 10; i++)
      {
        int row = RNG::range(start_coord.first + 1, end_coord.first - 1);
        int col = RNG::range(start_coord.second + 1, end_coord.second - 1);

        TilePtr tile = map->at(row, col);

        if (tile && tile->get_tile_super_type() == TileSuperType::TILE_SUPER_TYPE_GROUND && !tile->has_feature())
        {
          FeaturePtr bench = FeatureGenerator::generate_bench();
          tile->set_feature(bench);
          num_placed++;

          if (num_placed == num_benches)
          {
            break;
          }
        }
      }
    }
  }

  return generated;
}

bool PublicAreaSectorFeatureGenerator::generate_shop(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    CardinalDirection door_dir = static_cast<CardinalDirection>(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST));
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false);
    ShopGenerator sg;

    vector<Building> buildings;
    bool b_gen = SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, 100);

    if (b_gen)
    {
      generated = sg.generate_shop(map, buildings.at(0));
    }
  }

  return generated;
}

bool PublicAreaSectorFeatureGenerator::generate_plaza(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    GeneratorUtils::fill(map, start_coord, end_coord, TileType::TILE_TYPE_DUNGEON);

    if (CoordUtils::get_height(start_coord, end_coord) >= MIN_PLAZA_FOUNTAIN_HEIGHT && 
        CoordUtils::get_width(start_coord, end_coord) >= MIN_PLAZA_FOUNTAIN_WIDTH)
    {
      int mid_row = (start_coord.first + end_coord.first) / 2;
      int mid_col = (start_coord.second + end_coord.second) / 2;

      for (int f_row = mid_row - 1; f_row <= mid_row + 1; f_row++)
      {
        for (int f_col = mid_col - 1; f_col <= mid_col + 1; f_col++)
        {
          FeaturePtr fountain = FeatureGenerator::generate_fountain();
          TilePtr tile = map->at(f_row, f_col);

          if (tile && !tile->has_feature())
          {
            tile->set_feature(fountain);
            IInventoryPtr inv = tile->get_items();

            // Pennies in the fountain
            ItemManager::create_item_with_probability(1, 3, inv, ItemIdKeys::ITEM_ID_CURRENCY, static_cast<uint>(RNG::range(2, 10)));
          }
        }
      }
    }

    generated = true;
  }

  return generated;
}

bool PublicAreaSectorFeatureGenerator::should_generate_perimeter_statue(const int row, const int col, const Coordinate& start_coord, const Coordinate& end_coord, int row_cnt, int col_cnt)
{
  Coordinate cur_loc = {row, col};

  return (CoordUtils::is_in_perimeter(make_pair(row, col), start_coord, end_coord) &&
         (cur_loc != start_coord && cur_loc != make_pair(start_coord.first, end_coord.second) && cur_loc != make_pair(end_coord.first, start_coord.second) && cur_loc != end_coord) &&
         ((row == start_coord.first || row == end_coord.first) && (col_cnt % 2 == 0)) || ((col == start_coord.second || col == end_coord.second) && (row_cnt % 2 == 0)));
}

PublicSectorFeatureType PublicAreaSectorFeatureGenerator::get_random_feature(const int feat_idx) const
{
  for (const auto f_pair : features)
  {
    if (feat_idx < f_pair.first)
    {
      return f_pair.second;
    }
  }

  return PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK;
}

