#include "VegetableGardenGenerator.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

VegetableGardenGenerator::VegetableGardenGenerator(MapPtr base_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width)
: GardenGenerator(base_map, map_window_start_row, map_window_start_col, map_window_height, map_window_width),
vegetable_min(1), vegetable_max(1)
{
  populate_vegetable_map();
}

void VegetableGardenGenerator::populate_vegetable_map()
{
  vegetable_map.clear();
  vegetable_map = std::map<int, std::string>{{1, ItemIdKeys::ITEM_ID_VEGETABLE_1},
                                             {2, ItemIdKeys::ITEM_ID_VEGETABLE_2},
                                             {3, ItemIdKeys::ITEM_ID_VEGETABLE_3},
                                             {4, ItemIdKeys::ITEM_ID_VEGETABLE_4},
                                             {5, ItemIdKeys::ITEM_ID_VEGETABLE_5},
                                             {6, ItemIdKeys::ITEM_ID_VEGETABLE_6}};
  
  vegetable_min = 1;
  vegetable_max = 6;
}

void VegetableGardenGenerator::generate()
{
  plant_vegetables();
}

void VegetableGardenGenerator::plant_vegetables()
{
  TileGenerator tg;

  for (int col = window_start_col; col <= window_start_col + window_width; col++)
  {
    int vegetable_idx = RNG::range(vegetable_min, vegetable_max);

    string vegetable_id = vegetable_map[vegetable_idx];

    // Spaces needed between vegetables to ensure that things grow.
    for (int row = window_start_row; row <= window_start_row + window_height; row++)
    {
      TilePtr field_tile = tg.generate(TILE_TYPE_FIELD);
      
      // Every other column should be empty.
      if ((col % 3 == 0) && (row % 2 == 0))
      {
        // Generate a column of a particular vegetable.
        ItemPtr veg = ItemManager::create_item(vegetable_id);
        
        if (veg)
        {
          Inventory& inv = field_tile->get_items();
          inv.add(veg);
        }          
      }
    
      map->insert(row, col, field_tile);      
    }
  }
}

