#include "CurrentCreatureAbilities.hpp"
#include "MapUtils.hpp"
#include "MovementTextKeys.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "TileMovementConfirmation.hpp"

using namespace std;

// Check to see if movement needs to be confirmed.  First check to see if the tile is dangerous,
// and then check any additional special cases, such as swimming, etc.
pair<bool, string> TileMovementConfirmation::get_confirmation_details(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile)
{
  pair<bool, string> confirmation_details;
  confirmation_details.first = false;

  CurrentCreatureAbilities cca;
  bool is_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  bool is_flying = creature && creature->has_status(StatusIdentifiers::STATUS_ID_FLYING);
  FeaturePtr new_tile_feature = new_tile->get_feature();
  bool feature_dangerous = new_tile_feature && new_tile_feature->get_is_dangerous();

  if (cca.can_see(creature))
  {
    // Tile confirmation only happens if the creature can see.  Otherwise,
    // the creature has no idea that the place they're moving into is dangerous.
    if ((new_tile->get_dangerous(creature) && !is_incorporeal && !is_flying) ||
      (feature_dangerous && !is_flying))
    {
      confirmation_details.first = true;
      string confirmation_sid = new_tile->get_danger_confirmation_sid();

      if (feature_dangerous)
      {
        confirmation_sid = MovementTextKeys::ACTION_MOVE_DANGEROUS_FEATURE;
      }

      confirmation_details.second = TextMessages::get_confirmation_message(confirmation_sid);
    }
    else
    {
      pair<bool, string> swimming = check_for_jumping_into_water(creature, old_tile, new_tile);

      if (swimming.first)
      {
        confirmation_details = swimming;
      }
    }
  }

  return confirmation_details;
}

pair<bool, string> TileMovementConfirmation::check_for_jumping_into_water(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile)
{
  pair<bool, string> details;
  details.first = false;
  bool is_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  bool is_flying = creature && creature->has_status(StatusIdentifiers::STATUS_ID_FLYING);
  
  // If there get to be enough of these, break these out into a map or a class or something.
  // Probably should break out of MapUtils...
  if (MapUtils::is_moving_from_land_type_tile_to_water_type_tile(old_tile, new_tile))
  {
    IInventoryPtr inv = creature->get_inventory();

    if (!(creature->can_breathe(BreatheType::BREATHE_TYPE_WATER)) && !is_incorporeal && !is_flying && !inv->has_item_type(ItemType::ITEM_TYPE_BOAT))
    {
      details.first  = true;
      details.second = TextMessages::get_confirmation_message(TextKeys::DECISION_JUMP_INTO_WATER);
    }
  }
  
  return details;
}
