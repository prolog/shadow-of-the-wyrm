#include "CurrentCreatureAbilities.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MovementTextKeys.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "TileMovementConfirmation.hpp"

using namespace std;

// Check to see if movement needs to be confirmed.  First check to see if the tile is dangerous,
// and then check any additional special cases, such as swimming, etc.
tuple<bool, string, string> TileMovementConfirmation::get_confirmation_details(CreaturePtr creature, MapPtr map, TilePtr old_tile, const Coordinate& old_tile_coords, TilePtr new_tile, const Coordinate& new_tile_coords)
{
  tuple<bool, string, string> confirmation_details = { false, "", "" };

  CurrentCreatureAbilities cca;
  bool is_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  bool is_flying = creature && creature->has_status(StatusIdentifiers::STATUS_ID_FLYING);
  bool can_move_safely = (is_incorporeal || is_flying);
  FeaturePtr new_tile_feature = new_tile->get_feature();
  bool feature_dangerous = new_tile_feature && new_tile_feature->get_is_dangerous();

  if (creature != nullptr && new_tile != nullptr && cca.can_see(creature))
  {
    // Tile confirmation only happens if the creature can see.  Otherwise,
    // the creature has no idea that the place they're moving into is dangerous.
    if ((new_tile->get_dangerous(creature) || feature_dangerous) && !can_move_safely)
    {
      std::get<0>(confirmation_details) = true;
      string confirmation_sid = new_tile->get_danger_confirmation_sid();

      if (feature_dangerous)
      {
        confirmation_sid = MovementTextKeys::ACTION_MOVE_DANGEROUS_FEATURE;
      }

      if (!confirmation_sid.empty())
      {
        std::get<1>(confirmation_details) = TextMessages::get_confirmation_message(confirmation_sid);
      }
    }
    else if (MapUtils::is_in_shop_or_adjacent(map, old_tile_coords).first &&
            !MapUtils::is_in_shop_or_adjacent(map, new_tile_coords).first &&
             creature->has_unpaid_items())
    {
      confirmation_details = {true, TextMessages::get_confirmation_message(ActionTextKeys::ACTION_LEAVE_WITH_UNPAID_GOODS_CONFIRM), SoundEffectID::ALARM};
    }
    else
    {
      tuple<bool, string, string> swimming = check_for_jumping_into_water(creature, old_tile, new_tile);

      if (std::get<0>(swimming))
      {
        confirmation_details = swimming;
      }
    }
  }

  return confirmation_details;
}

tuple<bool, string, string> TileMovementConfirmation::check_for_jumping_into_water(CreaturePtr creature, TilePtr old_tile, TilePtr new_tile)
{
  Game& game = Game::instance();
  Season season = game.get_current_world()->get_calendar().get_season()->get_season();

  tuple<bool, string, string> details = { false, "", "" };
  bool is_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  bool is_frozen = new_tile->get_is_frozen(season);
  bool is_flying = creature && creature->has_status(StatusIdentifiers::STATUS_ID_FLYING);
  
  // If there get to be enough of these, break these out into a map or a class or something.
  // Probably should break out of MapUtils...
  if (MapUtils::is_moving_from_land_type_tile_to_water_type_tile(old_tile, new_tile))
  {
    IInventoryPtr inv = creature->get_inventory();

    if (!(creature->can_breathe(BreatheType::BREATHE_TYPE_WATER)) 
     && !is_incorporeal 
     && !is_frozen
     && !is_flying 
     && !inv->has_item_type(ItemType::ITEM_TYPE_BOAT))
    {
      std::get<0>(details) = true;
      std::get<1>(details) = TextMessages::get_confirmation_message(TextKeys::DECISION_JUMP_INTO_WATER);
      std::get<2>(details) = SoundEffectID::SPLASH;
    }
  }
  
  return details;
}
