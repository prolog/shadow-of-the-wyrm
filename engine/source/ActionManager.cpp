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
