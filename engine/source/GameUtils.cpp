#include "CoordUtils.hpp"
#include "GameUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"

using namespace std;

GameUtils::GameUtils()
{
}

void GameUtils::make_map_permanent(Game& game, CreaturePtr creature, MapPtr current_map)
{
  if (current_map != nullptr)
  {
    current_map->set_permanent(true);
    string current_map_id = current_map->get_map_id();
    game.get_map_registry_ref().set_map(current_map_id, current_map);

    // Assumption: if a creature (realistically, the player) is in a
    // previously-random map on the overworld, it is connected to
    // the player's position on that map.
    MapPtr world_map = game.get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);

    if (world_map != nullptr)
    {
      Coordinate location = world_map->get_location(creature->get_id());
      TilePtr creature_wm_tile = world_map->at(location);

      if (creature_wm_tile != nullptr)
      {
        creature_wm_tile->set_custom_map_id(current_map_id);
      }
    }
  }
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
    ActionCoordinator& ac = game.get_action_coordinator_ref();
    ActionCost cost = ac.get_current_action_cost();
    cost.set_cost(cost.get_cost() + 1);

    // Set the action cost to one more than the current.
    game.get_action_coordinator_ref().add(cost, new_creature->get_id());
  }
}

// Check to see if a particular creature exists within the player's view map.
bool GameUtils::is_creature_in_player_view_map(Game& game, const string& creature_id)
{
  bool creature_in_view_map = false;

  MapPtr map = game.get_current_map();
  CreaturePtr player = game.get_current_player();

  if (player)
  {
    MapPtr view_map = player->get_decision_strategy()->get_fov_map();

    if (view_map)
    {
      // Rebuild the view map's creatures in case it is out of date - the player 
      // might not have acted in some time...
      std::map<string, CreaturePtr>& creatures = view_map->get_creatures_ref();

      creature_in_view_map = (creatures.find(creature_id) != creatures.end());
    }
  }

  return creature_in_view_map;
}

// Check to see if two creature are adjacent on the current map.
bool GameUtils::is_creature_adjacent(Game& game, CreaturePtr creature1, CreaturePtr creature2)
{
  bool creatures_adjacent = false;
  MapPtr map = game.get_current_map();

  if (creature1 && creature2)
  {
    Coordinate c1 = map->get_location(creature1->get_id());
    Coordinate c2 = map->get_location(creature2->get_id());

    creatures_adjacent = CoordUtils::are_coordinates_adjacent(c1, c2);
  }

  return creatures_adjacent;
}

// Is the player among the creatures provided?
bool GameUtils::is_player_among_creatures(CreaturePtr creature1, CreaturePtr creature2)
{
  return ((creature1 && creature1->get_is_player()) || (creature2 && creature2->get_is_player()));
}

// How many seconds since the game started?
double GameUtils::get_seconds(Game& game)
{
  return game.get_current_world()->get_calendar().get_seconds();
}