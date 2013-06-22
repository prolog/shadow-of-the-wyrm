#include "CairnTileConfiguration.hpp"
#include "ItemManager.hpp"

void CairnTileConfiguration::configure(TilePtr tile, const Season season) const
{
  ItemManager::create_item_with_probability(1, 5, tile->get_items(), ItemIdKeys::ITEM_ID_ROCK);
}

