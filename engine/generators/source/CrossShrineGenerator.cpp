#include "CrossShrineGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"

using namespace std;

CrossShrineGenerator::CrossShrineGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_SHRINE), base_map(new_base_map)
{
}

MapPtr CrossShrineGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr CrossShrineGenerator::generate()
{
  MapPtr map = make_shared<Map>(*base_map);
  Dimensions dim = map->size();

  int num_rows = dim.get_y();
  int mid_row = num_rows / 2;
  int start_row = RNG::range(mid_row * 0.2, mid_row * 0.4);
  int shrine_height = 2 * std::abs(mid_row - start_row);

  int num_cols = dim.get_x();
  int mid_col = num_cols / 2;

  // Cross-shaped shrines have height = width
  int shrine_width = shrine_height;

  int start_col = mid_col - (shrine_width / 2);
  int wide_start_row = mid_row - (shrine_width / 4);
  int wide_start_col = start_col - (shrine_width / 2);
  int wide_width = shrine_width * 2;

  generate_building(map, start_row, start_col, mid_row, shrine_height, shrine_width, wide_start_row, wide_start_col, wide_width);
  generate_entrances(map, start_row, shrine_height, mid_col);
  generate_relic(map, {{wide_start_row, wide_start_col + 2}, {wide_start_row, wide_start_col + wide_width - 2}});

  return map;
}

void CrossShrineGenerator::generate_building(MapPtr map, const int start_row, const int start_col, const int mid_row, const int shrine_height, const int shrine_width, const int wide_start_row, const int wide_start_col, const int wide_width)
{
  // Generate the tall bit
  GeneratorUtils::generate_building(map, start_row, start_col, shrine_height, shrine_width);

  // Generate the wide bit
  int wide_height = shrine_height / 2;
  GeneratorUtils::generate_building(map, wide_start_row, wide_start_col, wide_height, wide_width);

  // Get rid of the walls in the middle
  vector<int> rows = { wide_start_row, wide_start_row + wide_height - 1 };
  for (int row : rows)
  {
    for (int col = start_col + 1; col < (start_col + shrine_width - 1); col++)
    {
      TilePtr dungeon_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(row, col, dungeon_tile);
    }
  }
}

void CrossShrineGenerator::generate_entrances(MapPtr map, const int start_row, const int shrine_height, const int mid_col)
{
  int end_row = start_row + shrine_height - 1;
  vector<Coordinate> entrances;

  for (int row : {start_row, end_row})
  {
    for (int col : {mid_col - 1, mid_col, mid_col + 1})
    {
      entrances.push_back({ row,col });
    }
  }

  for (const Coordinate& entr : entrances)
  {
    TilePtr dungeon_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
    map->insert(entr, dungeon_tile);
  }
}

void CrossShrineGenerator::generate_relic(MapPtr map, const vector<Coordinate>& options)
{
  if (map != nullptr && !options.empty())
  {
    Coordinate c = options.at(RNG::range(0, options.size()-1));

    // JCD FIXME refactor and reconsider includes
    string relic_id = get_additional_property(MapProperties::MAP_PROPERTIES_RELIC_ID);

    if (!relic_id.empty())
    {
      ItemManager im;

      ItemPtr relic = im.create_item(relic_id);
      TilePtr relic_tile = map->at(c);

      if (relic_tile != nullptr)
      {
        relic_tile->get_items()->add_front(relic);
      }
    }
  }
}