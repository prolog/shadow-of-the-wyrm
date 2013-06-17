#include "TreeTileConfiguration.hpp"
#include "ItemManager.hpp"

void TreeTileConfiguration::configure(TilePtr tile) const
{
  ItemManager::create_item_with_probability(1, 100, tile->get_items(), ItemIdKeys::ITEM_ID_BRANCH);
}

