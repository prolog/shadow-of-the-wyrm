#include "IcebergGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::vector;

const int IcebergGenerator::Y_DIVISOR_MIN = 5;
const int IcebergGenerator::Y_DIVISOR_MAX = 6;
const int IcebergGenerator::X_DIVISOR_MIN = 7;
const int IcebergGenerator::X_DIVISOR_MAX = 10;

IcebergGenerator::IcebergGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr IcebergGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_ICE);
  carve_edges(result_map);

  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  return result_map;
}

void IcebergGenerator::carve_edges(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();
    int y_divisor = RNG::range(Y_DIVISOR_MIN, Y_DIVISOR_MAX);
    int x_divisor = RNG::range(X_DIVISOR_MIN, X_DIVISOR_MAX);
    int y_range = rows / y_divisor;
    int x_range = cols / x_divisor;

    TileGenerator tg;
    TilePtr tile;

    // Carve away ice. Do a little less than the actual y/x ranges, so that a
    // meandering pass can be done afterwards to make the iceberg look more real.

    // Do both above and below the ice
    for (int i = 0; i <= y_range; i++)
    {
      for (int x = 0; x < cols; x++)
      {
        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({i, x}, tile);

        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({ rows - 1 - i, x }, tile);
      }
    }

    // Carve the left and right sides
    for (int i = 0; i < x_range; i++)
    {
      for (int y = 0; y < rows; y++)
      {
        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({ y, i }, tile);

        tile = tg.generate(TileType::TILE_TYPE_SEA);
        map->insert({ y, cols - 1 - i }, tile);
      }
    }

    erode_edges_further(map, rows, cols, y_range, x_range);
  }
}

void IcebergGenerator::erode_edges_further(MapPtr map, const int rows, const int cols, const int y_range, const int x_range)
{
  if (map != nullptr)
  {
    // Erode the corners - this makes the iceberg look less square and more
    // natural.
    erode_corners(map, rows, cols, y_range, x_range);

  //  // Do a drunken-ish walk around the iceberg
  //  TilePtr tile;
  //  TileType erosion_tt = TileType::TILE_TYPE_FIELD;
  //  TileGenerator tg;

  //  int y_cur = y_range;

  //  for (int x = x_range; x < cols - x_range; x++)
  //  {
  //    tile = tg.generate(erosion_tt);
  //    map->insert(y_cur, x, tile);
  //  }

  //  int x_cur = cols - x_range - 1;

  //  for (int y = y_range; y < rows - y_range; y++)
  //  {
  //    tile = tg.generate(erosion_tt);
  //    map->insert(y, x_cur, tile);
  //  }

  //  y_cur = rows - y_range - 1;

  //  for (int x = cols - x_range - 1; x >= x_range; x--)
  //  {
  //    tile = tg.generate(erosion_tt);
  //    map->insert(y_cur, x, tile);
  //  }

  //  x_cur = x_range;

  //  for (int y = rows - y_range - 1; y >= y_range; y--)
  //  {
  //    tile = tg.generate(erosion_tt);
  //    map->insert(y, x_cur, tile);
  //  }
  }
}

void IcebergGenerator::erode_corners(MapPtr map, const int rows, const int cols, const int y_range, const int x_range)
{
  if (map != nullptr)
  {
    vector<Coordinate> corners = { {y_range+1, x_range-1}, {y_range+1, cols-x_range-2}, {rows-y_range-2, cols-x_range-2}, {rows-y_range-2, x_range+1} };
    TileGenerator tg;
    TilePtr tile;

    for (const Coordinate& c : corners)
    {
      tile = tg.generate(TileType::TILE_TYPE_SEA);
      map->insert(c, tile);
    }
  }
}
