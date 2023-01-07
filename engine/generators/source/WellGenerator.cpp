#include "WellGenerator.hpp"
#include "BresenhamLine.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

WellGenerator::WellGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_WELL)
{
}

bool WellGenerator::get_allow_ancient_beasts() const
{
  return true;
}

MapPtr WellGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
  fill(result_map, TileType::TILE_TYPE_EARTH);

  int height = dimensions.get_y();
  int width = dimensions.get_x();
  Coordinate up_c(height / 2, width / 2);

  int open_height = RNG::range(height / 3, height / 2);
  int open_width = open_height;

  Coordinate open_start(up_c.first - open_height / 2, up_c.second - open_width / 2);
  Coordinate open_end(up_c.first + open_height / 2, up_c.second + open_width / 2);

  create_open_section(result_map, up_c, open_start, open_end);
  create_stream(result_map, open_start, open_end);

  // Create well and the way up in the centre.  Wells aren't multi-level, so
  // it's safe to always place the player on the up staircase.
  place_up_staircase(result_map, up_c.first, up_c.second, TileType::TILE_TYPE_FIELD, Direction::DIRECTION_UP, get_permanence(), true);

  return result_map;
}

bool WellGenerator::get_permanence_default() const
{
  return true;
}

MapType WellGenerator::get_map_type() const
{
  return MapType::MAP_TYPE_UNDERWORLD;
}

void WellGenerator::create_open_section(MapPtr result_map, const Coordinate& up_c, const Coordinate& open_start, const Coordinate& open_end)
{
  GeneratorUtils::fill(result_map, open_start, open_end, TileType::TILE_TYPE_DUNGEON);

  // Sometimes wells are wishing wells!
  if (RNG::percent_chance(50))
  {
    for (int row = open_start.first; row < open_end.first; row++)
    {
      for (int col = open_start.second; col < open_end.second; col++)
      {
        if (RNG::percent_chance(25))
        {
          ItemPtr ivory = ItemManager::create_item(ItemIdKeys::ITEM_ID_CURRENCY, static_cast<uint>(RNG::range(1, 4)));
          TilePtr tile = result_map->at(row, col);

          if (tile != nullptr)
          {
            tile->get_items()->merge_or_add(ivory, InventoryAdditionType::INVENTORY_ADDITION_BACK);
          }
        }
      }
    }
  }
}

void WellGenerator::create_stream(MapPtr result_map, const Coordinate& open_start, const Coordinate& open_end)
{
  Dimensions dim = result_map->size();

  int start_x = 0;
  int end_x = dim.get_x() - 1;
  int y_offset = RNG::range(0, open_start.first);
  int y_centre = (open_start.first + open_end.first) / 2;
  int start_y = y_centre - y_offset;
  int end_y = y_centre + y_offset;

  // 50% chance of a vertical-ish stream.
  if (RNG::percent_chance(50))
  {
    start_y = 0;
    end_y = dim.get_y() - 1;
    int x_offset = RNG::range(0, open_start.second);
    int x_centre = (open_start.second + open_end.second) / 2;
    start_x = x_centre - x_offset;
    end_x = x_centre + x_offset;
  }

  BresenhamLine bl;

  vector<Coordinate> coords = bl.get_points_in_line(start_y, start_x, end_y, end_x);
  TileGenerator tg;

  for (const Coordinate& c : coords)
  {
    TilePtr tile = tg.generate(TileType::TILE_TYPE_RIVER);
    result_map->insert(c, tile);
  }
}