#include "PlazaSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int PlazaSectorFeature::MIN_PLAZA_FOUNTAIN_HEIGHT = 5;
const int PlazaSectorFeature::MIN_PLAZA_FOUNTAIN_WIDTH = 5;

bool PlazaSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    GeneratorUtils::fill(map, start_coord, end_coord, TileType::TILE_TYPE_DUNGEON);

    if (CoordUtils::get_height(start_coord, end_coord) >= MIN_PLAZA_FOUNTAIN_HEIGHT &&
        CoordUtils::get_width(start_coord, end_coord) >= MIN_PLAZA_FOUNTAIN_WIDTH)
    {
      TileGenerator tg;

      // Wall border
      Coordinate wall_start_coord = { start_coord.first + 1, start_coord.second + 1 };
      Coordinate wall_end_coord = { end_coord.first - 1, end_coord.second - 1 };
      vector<Coordinate> wall_coords = CoordUtils::get_border_coordinates(wall_start_coord, wall_end_coord, 1);

      for (const Coordinate& c : wall_coords)
      {
        TilePtr wall_tile = tg.generate(TileType::TILE_TYPE_ROCK);
        map->insert(c, wall_tile);
      }

      // Centre fountains
      int mid_row = (start_coord.first+1 + end_coord.first-1) / 2;
      int mid_col = (start_coord.second+1 + end_coord.second-1) / 2;

      for (int f_row = mid_row - 1; f_row <= mid_row + 1; f_row++)
      {
        for (int f_col = mid_col - 1; f_col <= mid_col + 1; f_col++)
        {
          FeaturePtr fountain = FeatureGenerator::generate_fountain();
          TilePtr tile = map->at(f_row, f_col);

          if (tile && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON && !tile->has_feature())
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

