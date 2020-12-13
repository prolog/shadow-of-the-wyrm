#include "ParkSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

ParkSectorFeature::ParkSectorFeature()
: pct_chance_statues(75), pct_chance_trader(100), pct_chance_pond(75)
{
}

ParkSectorFeature::ParkSectorFeature(const int statues, const int trader, const int pond)
: pct_chance_statues(statues), pct_chance_trader(trader), pct_chance_pond(pond)
{
}

bool ParkSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  int height = CoordUtils::get_height(start_coord, end_coord);
  int width = CoordUtils::get_width(start_coord, end_coord);

  bool generate_benches = RNG::percent_chance(50);
  bool generate_statue_perimeter = RNG::percent_chance(pct_chance_statues);
  bool generate_trader = RNG::percent_chance(pct_chance_trader);
  bool generate_pond = !generate_statue_perimeter || RNG::percent_chance(pct_chance_pond);

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
          FeaturePtr statue = FeatureGenerator::generate_decorative_statue(dst);

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
          else if (RNG::percent_chance(10))
          {
            tile = tg.generate(TileType::TILE_TYPE_TREE);
          }
          else if (RNG::percent_chance(5))
          {
            tile = tg.generate(TileType::TILE_TYPE_EVERGREEN_TREE);
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

    if (generate_trader)
    {
      CreatureFactory cf;
      CreaturePtr vendor = cf.create_by_creature_id(Game::instance().get_action_manager_ref(), CreatureID::CREATURE_ID_VENDOR, map);

      Coordinate vendor_coord = { start_coord.first + 1, start_coord.second + 1 };
      TilePtr tile = map->at(vendor_coord);

      if (tile && vendor && MapUtils::is_tile_available_for_creature(vendor, tile))
      {
        GameUtils::add_new_creature_to_map(Game::instance(), vendor, map, vendor_coord);
      }
    }
  }

  return generated;
}

bool ParkSectorFeature::should_generate_perimeter_statue(const int row, const int col, const Coordinate& start_coord, const Coordinate& end_coord, int row_cnt, int col_cnt)
{
  Coordinate cur_loc = { row, col };

  return (CoordUtils::is_in_perimeter(make_pair(row, col), start_coord, end_coord) &&
         (cur_loc != start_coord && cur_loc != make_pair(start_coord.first, end_coord.second) && cur_loc != make_pair(end_coord.first, start_coord.second) && cur_loc != end_coord) &&
         (((row == start_coord.first || row == end_coord.first) && (col_cnt % 2 == 0)) || ((col == start_coord.second || col == end_coord.second) && (row_cnt % 2 == 0))));
}

