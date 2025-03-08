#include "AquaticVegetationTileConfiguration.hpp"
#include "ItemManager.hpp"

using namespace std;

void AquaticVegetationTileConfiguration::configure(TilePtr tile, const Season /*season*/) const
{
  IInventoryPtr tile_items = tile->get_items();

  // Kelp-the-item generates on kelp-the-tile at the same rate regardless of season.
  ItemManager::create_item_with_probability(1, 30, tile_items, ItemIdKeys::ITEM_ID_KELP);
}

