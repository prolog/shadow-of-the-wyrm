#include "ActionTextKeys.hpp"
#include "AutomaticMovementCoordinator.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"

using namespace std;

// Attempt to move automatically.
//
// To move automatically, the creature must be allowed to move automatically
// (no bad statuses like hunger, etc), the tile must allow automatic movement
// (not blocking, no creatures, etc), and the FOV must allow automatic
// movement as well (there can't be any hostile creatures that the creature
// can see).
ActionCostValue AutomaticMovementCoordinator::auto_move(CreaturePtr creature, MapPtr map, const Direction d)
{
  Game& game = Game::instance();

  vector<string> message_sids;
  AutomaticMovement& am = creature->get_automatic_movement_ref();
  ActionCostValue auto_move_cost = 0;
  bool auto_movement_engaged = false;
  TilePtr direction_tile = map->at(CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), d));

  pair<bool, vector<string>> creature_results = creature_can_auto_move(creature);
  bool creature_move = creature_results.first;
  copy(creature_results.second.begin(), creature_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> creature_position_results = creature_position_allows_auto_move(creature, map);
  bool creature_pos_move = creature_position_results.first;
  copy(creature_position_results.second.begin(), creature_position_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> tile_results = tile_allows_auto_move(creature, direction_tile);
  bool tile_move = tile_results.first;
  copy(tile_results.second.begin(), tile_results.second.end(), back_inserter(message_sids));

  pair<bool, vector<string>> map_results = fov_allows_auto_move(creature, creature->get_decision_strategy()->get_fov_map());
  bool map_move = map_results.first;
  copy(map_results.second.begin(), map_results.second.end(), back_inserter(message_sids));

  if (creature_move && creature_pos_move && tile_move && map_move)
  {
    MovementAction maction;
    auto_move_cost = maction.move(creature, d);
    TilePtr new_tile = MapUtils::get_tile_for_creature(map, creature);

    // If the creature wasn't able to move, disengage automovement.
    if (auto_move_cost > 0)
    {
      auto_movement_engaged = true;
    }

    // Only redraw when the creature actually moves - otherwise, the next turn
    // after disengaging will clear out any messages received at the end of
    // automovement, e.g., from ending on a tile containing items.
    if (creature && creature->get_is_player())
    {
      game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
      game.get_display()->redraw();
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

// Does the creature's position (current tile, and the surrounding ones) allow
// auto movement?
pair<bool, vector<string>> AutomaticMovementCoordinator::creature_position_allows_auto_move(CreaturePtr creature, MapPtr map)
{
  pair<bool, vector<string>> move_details = {false, {}};

  TilePtr current_tile = MapUtils::get_tile_for_creature(map, creature);

  // Stop auto-movement when moving to a tile that has items.
  if (current_tile && current_tile->get_items()->empty())
  {
    move_details.first = true;
  }

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

// Check to see if the field of view allows automatic movement into it by 
// checking to see if there are any creatures present that are hostile to 
// the creature doing the movement.
pair<bool, vector<string>> AutomaticMovementCoordinator::fov_allows_auto_move(CreaturePtr creature, MapPtr fov_map)
{
  pair<bool, vector<string>> fov_details;
  string automove_creature_id = creature->get_id();

  bool can_move = true;

  // Check the creatures in the FOV to see if any of them are hostile to the
  // creature currently moving.
  map<string, CreaturePtr> fov_creatures = fov_map->get_creatures();
  for(const CreatureMap::value_type& cpair : fov_creatures)
  {
    CreaturePtr fov_creature = cpair.second;
    if (fov_creature->hostile_to(automove_creature_id))
    {
      can_move = false;
      break;
    }
  }

  if (can_move == false)
  {
    fov_details.second.push_back(ActionTextKeys::ACTION_AUTOMOVE_HOSTILE_CREATURES);
  }

  fov_details.first = can_move;
  return fov_details;
}

// Check to see if the tile allows automatic movement into it by checking to 
// see if the tile is available (not empty, no blocking features, etc).
pair<bool, vector<string>> AutomaticMovementCoordinator::tile_allows_auto_move(CreaturePtr creature, TilePtr tile)
{
  pair<bool, vector<string>> tile_details;

  tile_details.first = (MapUtils::is_tile_available_for_creature(creature, tile));

  return tile_details;
}

