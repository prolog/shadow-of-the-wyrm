#include <string>
#include "global_prototypes.hpp"
#include "ActionManager.hpp"
#include "CharacterDumper.hpp"
#include "FileWriter.hpp"
#include "MessageManager.hpp"
#include "Log.hpp"

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

void ActionManager::dump_character(CreaturePtr creature)
{
  if (creature)
  {
    MessageManager* manager = MessageManager::instance();
    string name = creature->get_name();
    string dump_message = TextMessages::get_dumping_character_message(name);
    
    CharacterDumper dumper(creature);
    FileWriter file(creature->get_name());
    
    file.write(dumper.str());
    
    manager->add_new_message(dump_message);
    manager->send();
  }
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

// Do something with an item:
// - Equip it, or
// - Pick it up from the ground, or
// - Drop it on to the ground.
// 
// This function assumes everything is ok - it doesn't check for the overland map, any
// special terrain types, etc.
void ActionManager::handle_item(CreaturePtr creature, const ItemAction item_action, ItemPtr item)
{
  switch(item_action)
  {
    case ITEM_ACTION_EQUIP:
      item_manager.equip(creature, item);
      break;
    case ITEM_ACTION_PICK_UP:
      item_manager.pick_up(creature, item);
      break;
    case ITEM_ACTION_DROP:
      item_manager.drop(creature, item);
      break;
    default:
      Log::instance()->log("Error: Unhandled item action!");
      break;
  }
}

// Pick up an item, doing any necessary checks first.
void ActionManager::pick_up(CreaturePtr creature)
{
  if (creature)
  {
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      MessageManager* manager = MessageManager::instance();
      string pick_up_not_allowed = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED);
      
      manager->add_new_message(pick_up_not_allowed);
      manager->send();
    }
    else
    {
    }
  }
}

// Drop an item, doing any necessary checks first.
void ActionManager::drop(CreaturePtr creature)
{
  if (creature)
  {
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      MessageManager* manager = MessageManager::instance();
      string drop_not_allowed = StringTable::get(ActionTextKeys::ACTION_DROP_NOT_ALLOWED);
      
      manager->add_new_message(drop_not_allowed);
      manager->send();
    }
    else
    {
    }
  }
}
