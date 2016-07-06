#include "RectangularShrineGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"

using namespace std;

RectangularShrineGenerator::RectangularShrineGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_SHRINE), base_map(new_base_map)
{
}

MapPtr RectangularShrineGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr RectangularShrineGenerator::generate()
{
  MapPtr map = make_shared<Map>(*base_map);

  Dimensions dim = map->size();

  int num_rows = dim.get_y();
  int mid_row = num_rows / 2;
  int start_row = RNG::range(mid_row * 0.2, mid_row * 0.4);
  int shrine_height = 2 * std::abs(mid_row - start_row);

  int num_cols = dim.get_x();
  int mid_col = num_cols / 2;
  int start_col = RNG::range(mid_col * 0.2, mid_col * 0.4);
  int shrine_width = 2 * std::abs(mid_col - start_col);

  GeneratorUtils::generate_building(map, start_row, start_col, shrine_height, shrine_width);
  create_entrances(map, start_row, start_col, shrine_height, shrine_width, mid_row, mid_col);
  place_pillars(map, start_row, start_col, shrine_height, shrine_width, mid_row, mid_col);

  return map;
}

void RectangularShrineGenerator::create_entrances(MapPtr map, const int start_row, const int start_col, const int height, const int width, const int mid_row, const int mid_col)
{
  // Create entrances north, south, east, and west.
  // Each entrance is 3-wide, to prevent the player from bottling up monsters.
  if (map != nullptr)
  {
    // N, S
    vector<int> rows = {start_row, start_row + height - 1};

    for (int row : rows)
    {
      for (int col = mid_col - 1; col <= (mid_col + 1); col++)
      {
        TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
        map->insert(row, col, floor_tile);
      }
    }

    // E, W
    vector<int> cols = {start_col, start_col + width - 1};

    for (int col : cols)
    {
      for (int row = mid_row - 1; row <= (mid_row + 1); row++)
      {
        TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
        map->insert(row, col, floor_tile);
      }
    }
  }
}

void RectangularShrineGenerator::place_pillars(MapPtr map, const int start_row, const int start_col, const int height, const int width, const int mid_row, const int mid_col)
{
  if (map != nullptr)
  {
    // ...
  }
}