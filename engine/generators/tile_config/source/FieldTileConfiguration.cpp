#include "FieldTileConfiguration.hpp"
#include "ItemManager.hpp"

void FieldTileConfiguration::configure(TilePtr tile, const Season season) const
{
  ItemManager::create_item_with_probability(1, 200, tile->get_items(), ItemIdKeys::ITEM_ID_ROCK);
}

