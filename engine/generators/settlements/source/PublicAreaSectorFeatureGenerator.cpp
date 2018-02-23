#include "PublicAreaSectorFeatureGenerator.hpp"
#include "CoordUtils.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "ShopGenerator.hpp"
#include "StatueGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

PublicAreaSectorFeatureGenerator::PublicAreaSectorFeatureGenerator()
: features({{100, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_SHOP},
            {101, PublicSectorFeatureType::PUBLIC_SECTOR_FEATURE_PARK}})
{
}

bool PublicAreaSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx)
{
  bool created = false;
  PublicSectorFeatureType feat = get_random_feature(feat_idx);

  switch (feat)
  {
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

  bool generate_statue_perimeter = RNG::percent_chance(75);
  bool generate_pond = !generate_statue_perimeter || RNG::percent_chance(75);

  if (map != nullptr)
  {
    TileGenerator tg;
    TilePtr tile;

    for (int row = start_coord.first; row <= end_coord.first; row++)
    {
      for (int col = start_coord.second; col <= end_coord.second; col++)
      {
        tile = nullptr;

        if (generate_statue_perimeter && 
            CoordUtils::is_in_perimeter(make_pair(row, col), start_coord, end_coord) &&
            ((row + col) % 2 == 0))
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
          map->insert({row, col}, tile);
        }

        // For now, just to test things, set everything to fruit trees.
        if (!generated)
        {
          generated = true;
        }
      }
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
          map->insert({row, col}, tile);
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
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, CardinalDirection::CARDINAL_DIRECTION_NORTH, false);
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
