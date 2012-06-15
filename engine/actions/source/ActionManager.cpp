#include <string>
#include <boost/make_shared.hpp>
#include "ActionManager.hpp"
#include "CharacterDumpManager.hpp"
#include "Conversion.hpp"
#include "EquipmentManager.hpp"
#include "FileWriter.hpp"
#include "Game.hpp"
#include "InventoryManager.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "SearchActionManager.hpp"
#include "VersionActionManager.hpp"
#include "Log.hpp"

using namespace std;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

ActionCost ActionManager::version(CreaturePtr creature)
{
  VersionActionManager vam;
  return get_action_cost(creature, vam.version());
}

ActionCost ActionManager::dump_character(CreaturePtr creature)
{
  CharacterDumpManager cdm;
  return get_action_cost(creature, cdm.dump_character(creature));
}

bool ActionManager::search(CreaturePtr creature)
{
  SearchActionManager sam;
  sam.search(creature);
  return true;
}

bool ActionManager::move(CreaturePtr creature, const Direction direction)
{
  return movement_manager.move(creature, direction);
}

bool ActionManager::attack(CreaturePtr creature, const Direction direction)
{
  return combat_manager.attack(creature, direction);
}

// Move up a level
bool ActionManager::ascend(CreaturePtr creature)
{
  Game* game = Game::instance();
  
  if (game)
  {
    // If we're on the world map, send a message about not being able to ascend further.
    MapPtr current_map = game->get_current_map();
    MapType map_type = current_map->get_map_type();
    
    if (map_type == MAP_TYPE_WORLD && creature && creature->get_is_player())
    {
      MessageManager* manager = MessageManager::instance();
      string search_message = StringTable::get(MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP);

      manager->add_new_message(search_message);
      manager->send();
      
      return false;    
    } 
    
    movement_manager.ascend(creature);
  }
  
  return true;
}

// Move down a level
bool ActionManager::descend(CreaturePtr creature)
{
  return movement_manager.descend(creature);
}

// Remove an item from a particular slot.
// Return true if there was an item in the slot.
// Return false if there was no item in the slot.
bool ActionManager::remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location)
{
  if (creature)
  {
    ItemPtr item_in_slot = creature->get_equipment().get_item(worn_location);
    
    if (item_in_slot)
    {
      item_manager.remove(creature, worn_location);
      return true;
    }
  }
  
  return false;
}

// Wear or remove a particular item from the worn equipment by adding/removing the item from a slot.
void ActionManager::wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location)
{
  if (creature)
  {
    if (!remove_item(creature, worn_location)) // Wear an item - select something.
    {
      ItemPtr item_in_slot = inventory(creature, creature->get_inventory(), false);
      
      // This is null if no item was selected.
      if (item_in_slot)
      {        
        bool item_equipped = handle_item(creature, ITEM_ACTION_EQUIP, item_in_slot, worn_location);
        
        // If the item was successfully equipped, remove it from the
        // inventory.
        if (item_equipped)
        {
          string item_id = item_in_slot->get_id();
          creature->get_inventory().remove(item_id);
        }
      }
    }
  }
}

// Do something with an item:
// - Equip it, or
// - Pick it up from the ground, or
// - Drop it on to the ground.
// 
// This function assumes everything is ok - it doesn't check for the overland map, any
// special terrain types, etc.
bool ActionManager::handle_item(CreaturePtr creature, const ItemAction item_action, ItemPtr item, const EquipmentWornLocation loc)
{
  bool item_handled = true;
  
  switch(item_action)
  {
    case ITEM_ACTION_EQUIP:
      if (loc != EQUIPMENT_WORN_NONE) item_manager.equip(creature, item, loc);
      else item_manager.equip(creature, item);
      break;
    case ITEM_ACTION_PICK_UP:
      item_manager.pick_up(creature, item);
      break;
    case ITEM_ACTION_DROP:
      item_manager.drop(creature, item);
      break;
    default:
      Log::instance()->log("Error: Unhandled item action!");
      item_handled = false;
      break;
  }
  
  return item_handled;
}

// Pick up an item, doing any necessary checks first.
bool ActionManager::pick_up(CreaturePtr creature)
{
  bool advance_turn = false;

  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();
  
  if (creature && game)
  {
    MapPtr map = game->get_current_map();
    
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      string pick_up_not_allowed = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED);
      
      manager->add_new_message(pick_up_not_allowed);
      manager->send();
    }
    else
    {
      TilePtr tile = MapUtils::get_tile_for_creature(map, creature);
      
      if (tile)
      {
        Inventory& inv = tile->get_items();

        // If there is no item, inform the user.
        if (inv.empty())
        {
          if (creature->get_is_player())
          {
            string no_item_on_ground = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND);
            
            manager->add_new_message(no_item_on_ground);
            manager->send();
          }
        }
        else
        {
          // If there is one item, pick it up.
          uint num_items = inv.size();
          
          ItemPtr pick_up_item;
          
          if (num_items == 1)
          {
            pick_up_item = inv.at(0);
          }

          // If there are many items, get one of them.
          else
          {
            pick_up_item = inventory(creature, inv, false);
          }
          
          if (pick_up_item)
          {
            // Remove the item from the ground; add it to the creature's
            // inventory.
            inv.remove(pick_up_item->get_id());
            creature->get_inventory().add(pick_up_item);

            // Display a message if necessary
            if (creature->get_is_player())
            {
              string pick_up_message = TextMessages::get_item_pick_up_message(StringTable::get(pick_up_item->get_usage_description_sid()));
              
              manager->add_new_message(pick_up_message);
              manager->send();        
            }
          }
          
          // Advance the turn
          advance_turn = true;
        }   
      }      
    }
  }
  
  return advance_turn;
}

// Drop an item, doing any necessary checks first.
bool ActionManager::drop(CreaturePtr creature)
{
  bool advance_turn = false;
  
  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();
  
  if (game && creature)
  {
    MapPtr map = game->get_current_map();
    
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      string drop_not_allowed = StringTable::get(ActionTextKeys::ACTION_DROP_NOT_ALLOWED);
      
      manager->add_new_message(drop_not_allowed);
      manager->send();
    }
    else
    {
      ItemPtr item_to_drop = inventory(creature, creature->get_inventory(), false);
      
      if (!item_to_drop)
      {
        string no_item_to_drop = StringTable::get(ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED);
        
        manager->add_new_message(no_item_to_drop);
        manager->send();
      }
      else // Item selected
      {
        TilePtr creatures_tile = MapUtils::get_tile_for_creature(map, creature);
        
        if (creatures_tile)
        {
          // Add the item to the list currently on the tile.
          creatures_tile->get_items().add_front(item_to_drop);
        }
        
        // Remove it from the inventory
        creature->get_inventory().remove(item_to_drop->get_id());
        
        // Advance the turn
        advance_turn = true;
        
        // Display a message if appropriate.
        // If it's the player, remind the user what he or she dropped.
        if (creature->get_is_player())
        {
          string drop_message = TextMessages::get_item_drop_message(StringTable::get(item_to_drop->get_usage_description_sid()));
          
          manager->add_new_message(drop_message);
          manager->send();
        }
        // If it's not the player, and the player is in range, inform the player
        // what the creature dropped.
        else
        {
          
        }
      }      
    }
  }
  
  return advance_turn;
}

// Display the inventory; potentially select something.
ItemPtr ActionManager::inventory(CreaturePtr creature, Inventory& inv, const bool inventory_is_read_only)
{
  ItemPtr selected_item;
  
  Game* game = Game::instance();
  
  if (game && creature)
  {
    DisplayPtr game_display = game->get_display();
    InventoryManager inv_manager(game_display, creature);

    selected_item = inv_manager.manage_inventory(inv, inventory_is_read_only);
  }
  
  return selected_item;
}

// Wear/unwear equipment
void ActionManager::equipment(CreaturePtr creature)
{
  Game* game = Game::instance();
  
  if (game && creature)
  {
    DisplayPtr game_display = game->get_display();
    
    EquipmentManager equipment_manager(game_display, creature);
    equipment_manager.manage_equipment();
  }
}

// Create an ActionCost based on the ActionCostValue already generated
ActionCost ActionManager::get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value)
{
  ActionCostValue total_action_cost_value = 0;
  
  if (creature && (action_cost_value > 0))
  {
    total_action_cost_value = creature->get_speed().get_current() + action_cost_value;
  }
  
  ActionCost ac(total_action_cost_value);
  return ac;
}
