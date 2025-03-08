#include "WheatTileConfiguration.hpp"
#include "ItemManager.hpp"

void WheatTileConfiguration::configure(TilePtr tile, const Season /*season*/) const
{
  IInventoryPtr tile_items = tile->get_items();
  ItemManager::create_item_with_probability(1, 5, tile_items, ItemIdKeys::ITEM_ID_WHEAT);
}

