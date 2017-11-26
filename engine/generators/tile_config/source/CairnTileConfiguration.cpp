#include "CairnTileConfiguration.hpp"
#include "ItemManager.hpp"

void CairnTileConfiguration::configure(TilePtr tile, const Season season) const
{
  IInventoryPtr tile_items = tile->get_items();

  bool created_rock = ItemManager::create_item_with_probability(1, 5, tile_items, ItemIdKeys::ITEM_ID_ROCK);

  if (!created_rock)
  {
    ItemManager::create_item_with_probability(1, 6, tile_items, ItemIdKeys::ITEM_ID_STONE);
  }

  if (!created_rock)
  {
    ItemManager::create_item_with_probability(1, 10, tile_items, ItemIdKeys::ITEM_ID_HUGE_ROCK);
  }
}

