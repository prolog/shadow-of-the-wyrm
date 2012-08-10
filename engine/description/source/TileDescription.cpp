#include "DescriberFactory.hpp"
#include "TileDescription.hpp"

using std::string;

// Get the description for the tile, based on the following:
// - Whether the tile is non-null
// - Whether it contains a creature
// - Whether it contains a feature
// - Whether it contains items
string TileDescription::describe(TilePtr tile, bool tile_is_in_fov)
{
  string tile_description;

  if (tile)
  {
    // If the tile hasn't been explored, get a message saying so.
    if (!tile->get_explored())
    {
      tile_description = StringTable::get(ActionTextKeys::ACTION_LOOK_UNEXPLORED_TILE);
    }
    // Otherwise, get details from the tile.
    else
    {
      IDescriberPtr describer = DescriberFactory::create_describer(tile);
      tile_description = describer->describe();

      if (tile_is_in_fov)
      {        
    /*    CreatureDescriber cd;
        CreaturePtr creature = tile->get_creature();
        tile_description += cd.describe(creature); */
        
        FeaturePtr feature = tile->get_feature();
        describer = DescriberFactory::create_describer(feature);
        tile_description += describer->describe();
        
    /*    InventoryDescriber id;
        Inventory& inventory = tile->get_items();
        tile_description += id.describe(inventory); */              
      }
      // If the tile's been explored, but is out of range, add another message.
      else
      {
        tile_description += StringTable::get(ActionTextKeys::ACTION_LOOK_TILE_OUT_OF_RANGE);
      }
    }
  }

  return tile_description;
}
