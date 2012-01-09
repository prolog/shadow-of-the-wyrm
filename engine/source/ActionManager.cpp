#include <string>
#include "global_prototypes.hpp"
#include "ActionManager.hpp"
#include "MessageManager.hpp"

using namespace std;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

void ActionManager::set_current_map(MapPtr new_map)
{
  map = new_map;
  movement_manager.set_current_map(map);
}

void ActionManager::version()
{
  MessageManager* manager = MessageManager::instance();
  string game_version = get_game_version_synopsis();

  manager->add_new_message(game_version);
  manager->send();
}

void ActionManager::search(CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    MessageManager* manager = MessageManager::instance();
    string search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH);

    manager->add_new_message(search_message);
    manager->send();

    // JCD FIXME: Add actual search to see if anything hidden was spotted.
  }
}

void ActionManager::move(CreaturePtr creature, const Direction direction)
{
  movement_manager.move(creature, direction);
}

// Move up a level
void ActionManager::ascend(CreaturePtr creature)
{
  // If we're on the world map, send a message about not being able to ascend further.
  MapType map_type = map->get_map_type();
  
  if (map_type == MAP_TYPE_WORLD && creature && creature->get_is_player())
  {
    MessageManager* manager = MessageManager::instance();
    string search_message = StringTable::get(ActionTextKeys::ACTION_NO_WAY_UP_WORLD_MAP);

    manager->add_new_message(search_message);
    manager->send();    
  }
  
  // Otherwise, check to see if the creature is on an up-staircase, and go from there.
  // ...
}

// Move down a level
void ActionManager::descend(CreaturePtr creature)
{
  // If we're on the world map, we can always descend.
  
  // Check to see if the creature is on a down-staircase, and go from there.
}
