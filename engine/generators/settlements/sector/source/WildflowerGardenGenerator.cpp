#include "WildflowerGardenGenerator.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;

WildflowerGardenGenerator::WildflowerGardenGenerator(MapPtr new_base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width)
: GardenGenerator(new_base_map, map_window_start_row, map_window_start_col, map_window_height, map_window_width),
wildflower_rand_min(1), wildflower_rand_max(6)
{
  initialize_generator();
}

void WildflowerGardenGenerator::generate()
{
  seed_flowers();
}

void WildflowerGardenGenerator::initialize_generator()
{
  populate_wildflower_ids();
}

void WildflowerGardenGenerator::populate_wildflower_ids()
{
  wildflower_item_ids.clear();
  wildflower_item_ids = std::map<int, std::string>{{1, ItemIdKeys::ITEM_ID_WILDFLOWER_1},
                                                   {2, ItemIdKeys::ITEM_ID_WILDFLOWER_2},
                                                   {3, ItemIdKeys::ITEM_ID_WILDFLOWER_3},
                                                   {4, ItemIdKeys::ITEM_ID_WILDFLOWER_4},
                                                   {5, ItemIdKeys::ITEM_ID_WILDFLOWER_5},
                                                   {6, ItemIdKeys::ITEM_ID_WILDFLOWER_6}};
}

void WildflowerGardenGenerator::seed_flowers()
{
  TilePtr flower_tile;
  TileGenerator tg;
  int rand_flower;
  
  for (int row = window_start_row; row <= window_start_row + window_height; row++)
  {
    for (int col = window_start_col; col <= window_start_col + window_width; col++)
    {
      // Generate the field tile, and then "plant" the flower on top.
      flower_tile = tg.generate(TileType::TILE_TYPE_FIELD);

      if (RNG::percent_chance(75))
      {
        rand_flower = RNG::range(wildflower_rand_min, wildflower_rand_max);
        string flower_item_id = wildflower_item_ids[rand_flower];
        ItemPtr flower = ItemManager::create_item(flower_item_id);
        
        if (flower)
        {
          IInventoryPtr inv = flower_tile->get_items();
          inv->add(flower);
        }
      }
      
      map->insert(row, col, flower_tile);
    }
  }
}
