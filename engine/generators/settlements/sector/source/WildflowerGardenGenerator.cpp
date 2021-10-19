#include "WildflowerGardenGenerator.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

WildflowerGardenGenerator::WildflowerGardenGenerator(const string& new_deity_id, const AlignmentRange new_ar)
: GardenSectorFeature(new_deity_id, new_ar), wildflower_rand_min(1), wildflower_rand_max(6)
{
  initialize_generator();
}

void WildflowerGardenGenerator::initialize_generator()
{
  populate_wildflower_ids();
}

pair<pair<int, int>, map<int, string>> WildflowerGardenGenerator::get_wildflower_details() const
{
  return make_pair(make_pair(wildflower_rand_min, wildflower_rand_max), wildflower_item_ids);
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

void WildflowerGardenGenerator::plant_flower(TilePtr tile)
{
  if (tile != nullptr)
  {
    int rand_flower = RNG::range(wildflower_rand_min, wildflower_rand_max);
    string flower_item_id = wildflower_item_ids[rand_flower];
    ItemPtr flower = ItemManager::create_item(flower_item_id);

    if (flower)
    {
      IInventoryPtr inv = tile->get_items();
      inv->merge_or_add(flower, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
    }
  }
}

bool WildflowerGardenGenerator::generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  TilePtr flower_tile;
  TileGenerator tg;
  
  for (int row = start_coord.first; row <= end_coord.first; row++)
  {
    for (int col = start_coord.second; col <= end_coord.second; col++)
    {
      // Generate the field tile, and then "plant" the flower on top.
      flower_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      plant_flower(flower_tile);
      
      map->insert(row, col, flower_tile);
    }
  }

  return true;
}
