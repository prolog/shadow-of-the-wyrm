#include "PublicAreaSectorFeatureGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

bool PublicAreaSectorFeatureGenerator::create_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const int feat_idx)
{
  bool created = false;
  PublicSectorFeatureType feat = static_cast<PublicSectorFeatureType>(feat_idx);

  switch (feat)
  {
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

  if (map != nullptr)
  {
    TileGenerator tg;

    for (int row = start_coord.first; row <= end_coord.first; row++)
    {
      for (int col = start_coord.second; col <= end_coord.second; col++)
      {
        TilePtr tile = tg.generate(TileType::TILE_TYPE_FRUIT_TREE);
        map->insert(make_pair(row, col), tile);

        // For now, just to test things, set everything to fruit trees.
        if (!generated)
        {
          generated = true;
        }
      }
    }
  }

  return generated;
}

int PublicAreaSectorFeatureGenerator::get_min_feature_idx() const
{
  return static_cast<int>(PublicSectorFeatureType::PUBLIC_SECTOR_FIRST);
}

int PublicAreaSectorFeatureGenerator::get_max_feature_idx() const
{
  return static_cast<int>(PublicSectorFeatureType::PUBLIC_SECTOR_LAST);
}
