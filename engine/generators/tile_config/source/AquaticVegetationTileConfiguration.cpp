#include "AquaticVegetationTileConfiguration.hpp"
#include "ItemManager.hpp"

using namespace std;

void AquaticVegetationTileConfiguration::configure(TilePtr tile, const Season /*season*/) const
{
  IInventoryPtr tile_items = tile->get_items();

  // Kelp-the-item generates on kelp-the-tile regardless of season.
  ItemManager::create_item_with_probability(1, 2, tile_items, ItemIdKeys::ITEM_ID_KELP);
}

