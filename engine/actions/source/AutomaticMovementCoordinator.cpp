#include "ActionTextKeys.hpp"
#include "AutomaticMovementCoordinator.hpp"
#include "CoordUtils.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"

using namespace std;

ActionCostValue AutomaticMovementCoordinator::auto_move(CreaturePtr creature, MapPtr map, const Direction d)
{
  vector<string> message_sids;
  AutomaticMovement& am = creature->get_automatic_movement_ref();
  ActionCostValue auto_move_cost = 0;
  bool auto_movement_engaged = false;
  TilePtr direction_tile = map->at(CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), d));

  pair<bool, vector<string>> creature_results = creature_can_auto_move(creature);
  bool creature_move = creature_results.first;
  copy(creature_results.second.begin(), creature_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> tile_results = tile_allows_auto_move(creature, direction_tile);
  bool tile_move = tile_results.first;
  copy(tile_results.second.begin(), tile_results.second.end(), back_inserter(message_sids));

  if (creature_move && tile_move)
  {
    MovementAction maction;
    auto_move_cost = maction.move(creature, d);

    // If the creature wasn't able to move, disengage automovement.
    if (auto_move_cost > 0)
    {
      auto_movement_engaged = true;
    }
  }
  else
  {
    if (!message_sids.empty())
    {
      string first_message = message_sids.at(0);

      if (!first_message.empty() && creature->get_is_player())
      {
        IMessageManager& manager = MessageManagerFactory::instance();
        manager.add_new_message(StringTable::get(first_message));
        manager.send();
      }
    }
  }

  am.set_direction(d);
  am.set_engaged(auto_movement_engaged);

  return auto_move_cost;
}

// Check hunger and other attributes on the creature to determine if auto-move
// is allowed.
pair<bool, vector<string>> AutomaticMovementCoordinator::creature_can_auto_move(CreaturePtr creature)
{
  pair<bool, vector<string>> move_details;
  bool can_move = true;
  vector<string> message_sids;

  pair<bool, vector<string>> hunger_details = hunger_allows_auto_move(creature);
  copy(hunger_details.second.begin(), hunger_details.second.end(), back_inserter(message_sids));

  can_move = can_move && hunger_details.first;

  move_details.first = can_move;
  move_details.second = message_sids;

  return move_details;
}

// Check to see if the creature can automatically move, or if they are
// too hungry.
pair<bool, vector<string>> AutomaticMovementCoordinator::hunger_allows_auto_move(CreaturePtr creature)
{
  pair<bool, vector<string>> move_details;

  HungerClock& hunger = creature->get_hunger_clock_ref();

  // The creature can move if it is not the case that the creature's hunger
  // level is at hungry or worse.
  move_details.first = !((hunger.is_normal_or_worse() && (!hunger.is_normal())));
  if (move_details.first == false)
  {
    move_details.second.push_back(ActionTextKeys::ACTION_AUTOMOVE_TOO_HUNGRY);
  }

  return move_details;
}  

pair<bool, vector<string>> AutomaticMovementCoordinator::tile_allows_auto_move(CreaturePtr creature, TilePtr tile)
{
  pair<bool, vector<string>> tile_details;

  tile_details.first = (MapUtils::is_tile_available_for_creature(creature, tile));

  return tile_details;
}

