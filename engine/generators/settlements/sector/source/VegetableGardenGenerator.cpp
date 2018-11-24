#include "VegetableGardenGenerator.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

VegetableGardenGenerator::VegetableGardenGenerator(const string& new_deity_id, const AlignmentRange new_ar)
: GardenSectorFeature(new_deity_id, new_ar), vegetable_min(1), vegetable_max(1)
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

bool VegetableGardenGenerator::generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  TileGenerator tg;

  for (int col = start_coord.second; col <= end_coord.second; col++)
  {
    int vegetable_idx = RNG::range(vegetable_min, vegetable_max);

    string vegetable_id = vegetable_map[vegetable_idx];

    // Spaces needed between vegetables to ensure that things grow.
    for (int row = start_coord.first; row <= end_coord.first; row++)
    {
      TilePtr field_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      
      if ((col % 3 == 0) && (row % 2 == 0))
      {
        // Generate a column of a particular vegetable.
        ItemPtr veg = ItemManager::create_item(vegetable_id);
        
        if (veg)
        {
          IInventoryPtr inv = field_tile->get_items();
          inv->add(veg);
        }          
      }
    
      map->insert(row, col, field_tile);      
    }
  }

  return true;
}

