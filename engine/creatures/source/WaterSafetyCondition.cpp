#include "WaterSafetyCondition.hpp"
#include "Game.hpp"
#include "ItemProperties.hpp"

using namespace std;

// A water tile is safe if the creature breathes water, flies, or the creature 
// has a boat.
//
// Incorporeal creatures aren't safe crossing water: air-breathing creatures
// still need to breathe, and spirits (for reasons unknown) do not seem to
// be able to cross water...
bool WaterSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile)
{
  bool safe = false;

  if (creature != nullptr && tile != nullptr)
  {
    Game& game = Game::instance();
    ISeason* season = game.get_current_world()->get_calendar().get_season();

    // Frozen water is safe.
    if (tile->get_is_frozen(season->get_season()))
    {
      return true;
    }
    else
    {
      // If the water tile is deathly, flying or a boat will protect you.
      // Otherwise, the standard water conditions apply.
      if (tile->get_unprotected_movement_is_death(creature))
      {
        IInventoryPtr inv = creature->get_inventory();

        safe = (creature->has_status(StatusIdentifiers::STATUS_ID_FLYING) ||
                inv->has_item_type(ItemType::ITEM_TYPE_BOAT));

        // Submerged overrides everything else - a boat or flying on their
        // own don't help if you're submerged in deathly waters.
        if (tile->get_submerged())
        {
          safe = false;
        }

        // Having an item with the Nexus propety is the only way to be truly
        // safe in deathly waters.
        if (creature->has_item_with_property(ItemProperties::ITEM_PROPERTIES_NEXUS))
        {
          safe = true;
        }
      }
      else
      {
        if (creature->can_breathe(BreatheType::BREATHE_TYPE_WATER) ||
          creature->has_status(StatusIdentifiers::STATUS_ID_FLYING))
        {
          safe = true;
        }
        else
        {
          safe = creature->get_inventory()->has_item_type(ItemType::ITEM_TYPE_BOAT);
        }
      }
    }
  }

  return safe;
}

#ifdef UNIT_TESTS
#include "unit_tests/WaterSafetyCondition_test.cpp"
#endif