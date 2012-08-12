#include <string>
#include <boost/make_shared.hpp>
#include "ActionManager.hpp"
#include "CharacterDumpManager.hpp"
#include "Conversion.hpp"
#include "DateTimeManager.hpp"
#include "EquipmentManager.hpp"
#include "FileWriter.hpp"
#include "Game.hpp"
#include "InventoryManager.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "PrayerManager.hpp"
#include "SearchActionManager.hpp"
#include "VersionActionManager.hpp"
#include "WeaponInfoManager.hpp"
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

ActionCost ActionManager::date_and_time(CreaturePtr creature)
{
  DateTimeManager dtm;
  return get_action_cost(creature, dtm.date_and_time());
}

ActionCost ActionManager::dump_character(CreaturePtr creature)
{
  CharacterDumpManager cdm;
  return get_action_cost(creature, cdm.dump_character(creature));
}

ActionCost ActionManager::search(CreaturePtr creature)
{
  SearchActionManager sam;
  return get_action_cost(creature, sam.search(creature));
}

ActionCost ActionManager::move(CreaturePtr creature, const Direction direction)
{
  return get_action_cost(creature, movement_manager.move(creature, direction));
}

ActionCost ActionManager::attack(CreaturePtr creature, const Direction direction)
{
  return get_action_cost(creature, combat_manager.attack(creature, direction));
}

// Move up a level
ActionCost ActionManager::ascend(CreaturePtr creature)
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
      
      return get_action_cost(creature, 0);
    } 
    
    movement_manager.ascend(creature);
  }
  
  return get_action_cost(creature, 1); // JCD FIXME
}

// Move down a level
ActionCost ActionManager::descend(CreaturePtr creature)
{
  return get_action_cost(creature, movement_manager.descend(creature));
}

// Remove an item from a particular slot.
// Advance the turn if there was an item in the slot.
// Do not advance if there was no item in the slot.
ActionCostValue ActionManager::remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location)
{
  if (creature)
  {
    ItemPtr item_in_slot = creature->get_equipment().get_item(worn_location);
    
    if (item_in_slot)
    {
      item_manager.remove(creature, worn_location);
      return 1;
    }
  }
  
  return 0;
}

// Wear or remove a particular item from the worn equipment by adding/removing the item from a slot.
ActionCostValue ActionManager::wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location)
{
  ActionCostValue action_cost = 0;
  
  if (creature)
  {
    ActionCostValue item_removed = remove_item(creature, worn_location);
    action_cost = item_removed;
    
    if (!item_removed) // Wear an item - select something.
    {      
      ItemPtr item_in_slot = inventory(creature, creature->get_inventory(), worn_location, false);
      
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
          action_cost = 1;
        }
      }
    }
  }
  
  return action_cost;
}

// Do something with an item:
// - Equip it, or
// - Pick it up from the ground, or
// - Drop it on to the ground.
// 
// This function assumes everything is ok - it doesn't check for the overland map, any
// special terrain types, etc.
ActionCostValue ActionManager::handle_item(CreaturePtr creature, const ItemAction item_action, ItemPtr item, const EquipmentWornLocation loc)
{
  ActionCostValue action_cost_value = 1;
  
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
      action_cost_value = 0;
      break;
  }
  
  return action_cost_value;
}

// Pick up an item, doing any necessary checks first.
ActionCost ActionManager::pick_up(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
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
            pick_up_item = inventory(creature, inv, EQUIPMENT_WORN_NONE, false);
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
          action_cost_value = 1;
        }   
      }      
    }
  }

  return get_action_cost(creature, action_cost_value);
}

// Drop an item, doing any necessary checks first.
ActionCost ActionManager::drop(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
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
      ItemPtr item_to_drop = inventory(creature, creature->get_inventory(), EQUIPMENT_WORN_NONE, false);
      
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
        action_cost_value = 1;
        
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
  
  return get_action_cost(creature, action_cost_value);
}

// Display the inventory; potentially select something.
ItemPtr ActionManager::inventory(CreaturePtr creature, Inventory& inv, const EquipmentWornLocation ewl, const bool inventory_is_read_only)
{
  ItemPtr selected_item;
  
  Game* game = Game::instance();
  
  if (game && creature)
  {
    DisplayPtr game_display = game->get_display();
    InventoryManager inv_manager(game_display, creature);

    selected_item = inv_manager.manage_inventory(inv, ewl, inventory_is_read_only);
  }
  
  return selected_item;
}

// Wear/unwear equipment
ActionCost ActionManager::equipment(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  Game* game = Game::instance();
  
  if (game && creature)
  {
    DisplayPtr game_display = game->get_display();
    
    EquipmentManager equipment_manager(game_display, creature);
    action_cost_value = equipment_manager.manage_equipment();
  }

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::pray(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  Game* game = Game::instance();
  
  if (game && creature)
  {
    PrayerManager prayer_manager;
    action_cost_value = prayer_manager.pray(creature);
  }

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::weapon_info(CreaturePtr creature, const WeaponStyle weapon_style)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    WeaponInfoManager weapon_info_manager;
    
    switch(weapon_style)
    {
      case WEAPON_STYLE_MELEE:
        action_cost_value = weapon_info_manager.melee_weapon_info(creature);
        break;
      case WEAPON_STYLE_RANGED:
        action_cost_value = weapon_info_manager.ranged_weapon_info(creature);
        break;
      default:
        break;
    }    
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::select_tile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    action_cost_value = tile_selection_manager.select_tile(creature);
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCostValue ActionManager::select_tile(CreaturePtr creature, const Direction d)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    action_cost_value = tile_selection_manager.select_tile(creature, d);
  }
  
  return action_cost_value;
}

ActionCostValue ActionManager::select_tile_cancel(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    action_cost_value = tile_selection_manager.select_tile_cancel(creature);
  }
  
  return action_cost_value;
}

ActionCost ActionManager::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::quit(CreaturePtr creature)
{
  Game* game = Game::instance();
  
  if (game)
  {
    game->stop_playing();
  }
  
  return get_action_cost(creature, 1);
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

