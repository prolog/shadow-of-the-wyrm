#include "CurrentCreatureAbilities.hpp"
#include "MapUtils.hpp"
#include "ViewMapTranslator.hpp"

// Protected constructor and destructor.
ViewMapTranslator::ViewMapTranslator()
{
}

ViewMapTranslator::~ViewMapTranslator()
{
}

// Create a view map around a tile with a given size.  The size will be at most (size+size+1) x (size+size+1).
// The "+1" represents the centre row.  The original "size" is the maximum length that can be seen in a given
// direction.
MapPtr ViewMapTranslator::create_view_map_around_tile(CreaturePtr creature, MapPtr original_map, const Coordinate& centre, const int size)
{
  Dimensions original_dimensions = original_map->size();
  Dimensions dimensions = MapUtils::get_dimensions(original_map, centre, size);

  MapPtr view_map = std::make_shared<Map>(dimensions);
  view_map->set_original_size(original_dimensions);

  CurrentCreatureAbilities cca;
  if (cca.can_see(creature))
  {
    // Use the same shared pointer in most cases.  When there is something
    // hidden, create a copy of the shared_ptr and hide the details appropriately
    // so that the original tile is untouched.
    for (int row = centre.first - size; row <= (centre.first + size); row++)
    {
      for (int col = centre.second - size; col <= (centre.second + size); col++)
      {
        TilePtr current_tile = original_map->at(row, col);

        if (current_tile)
        {
          CreaturePtr tile_creature;
          bool hidden_cr = false;

          if (current_tile->has_creature())
          {
            tile_creature = current_tile->get_creature();
            hidden_cr = tile_creature->has_status(StatusIdentifiers::STATUS_ID_HIDE);
            current_tile = TilePtr(current_tile->clone());
          }

          view_map->insert(row, col, current_tile);

          if (hidden_cr && tile_creature)
          {
            MapUtils::remove_creature(view_map, tile_creature, true);
          }
        }
      }
    }
  }
  
  // Update the list of creatures/locations based on the current view.
  view_map->reset_creatures_and_locations();

  return view_map;
}


