#include "GameUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"

GameUtils::GameUtils()
{
}

// Add a new creature to the specified map.  If the specified map is the
// currently loaded map, ensure that the creature is also added
// appropriately to the Game's ActionCoordinator.
void GameUtils::add_new_creature_to_map(Game& game, CreaturePtr new_creature, MapPtr map, const Coordinate& coords)
{
  // Add the creature to the map.
  MapUtils::add_or_update_location(map, new_creature, coords);

  // Potentially add the creature to the action coordinator, if the
  // map is the current game map.
  MapPtr game_current_map = game.get_current_map();

  if (map->get_map_id() == game_current_map->get_map_id())
  {
    ActionCost cost;
    cost.set_cost(1);
    game.get_action_coordinator_ref().add(cost, new_creature->get_id());
  }
}

