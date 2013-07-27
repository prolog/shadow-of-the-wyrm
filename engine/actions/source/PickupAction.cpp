#include <list>
#include <boost/foreach.hpp>
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "Inventory.hpp"
#include "ItemFilterFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PickupAction.hpp"
#include "TextMessages.hpp"

using namespace std;

// Try to pick up.
ActionCostValue PickupAction::pick_up(CreaturePtr creature, ActionManager * const am)
{  
  ActionCostValue action_cost_value = 0;
  Game& game = Game::instance();
  
  if (creature)
  {
    MapPtr map = game.get_current_map();
    
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      handle_world_map_pickup(creature);
    }
    else
    {
      action_cost_value = handle_pickup(creature, map, am);
    }
  }

  return action_cost_value;
}

ActionCostValue PickupAction::handle_pickup(CreaturePtr creature, MapPtr map, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);
    
    if (tile)
    {
      Inventory& inv = tile->get_items();

      // If there is no item, inform the user.
      if (inv.empty())
      {
        handle_empty_tile_pickup(creature);
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
          list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
          pick_up_item = am->inventory(creature, inv, no_filter, false);
        }
        
        if (pick_up_item)
        {
          // Remove the item from the ground.
          inv.remove(pick_up_item->get_id());
          
          if (!merge_into_equipment(creature, pick_up_item))
          {
            merge_or_add_into_inventory(creature, pick_up_item);
          }
        }
        
        // Advance the turn
        action_cost_value = get_action_cost_value();
      }   
    }      
  }
  
  return action_cost_value;
}

// Handle the case where we're trying to pick up on the world map, which is an invalid case.
void PickupAction::handle_world_map_pickup(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);
  
  if (creature && creature->get_is_player())
  {
    string pick_up_not_allowed = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED);
    
    manager.add_new_message(pick_up_not_allowed);
    manager.send();
  }
}

// Handle the case where we're trying to pick up from a tile that contains no items.
void PickupAction::handle_empty_tile_pickup(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);
  
  if (creature && creature->get_is_player())
  {
    string no_item_on_ground = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND);
    
    manager.add_new_message(no_item_on_ground);
    manager.send();
  }  
}

// Merge into the equipment, if possible (true is returned).
// If the item can't be merged into the equipment, return false.
bool PickupAction::merge_into_equipment(CreaturePtr creature, ItemPtr item)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);
  
  if (creature)
  {
    Equipment& equipment = creature->get_equipment();
    
    if (equipment.merge(item))
    {
      string item_merged_into_equipment = TextMessages::get_item_pick_up_and_merge_message(item);
      manager.add_new_message(item_merged_into_equipment);
      manager.send();
      
      return true;
    }
  }
  
  return false;
}

// Merge into the inventory, if possible.  If this is not possible,
// add the item to the inventory.
bool PickupAction::merge_or_add_into_inventory(CreaturePtr creature, ItemPtr item)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);

  if (creature)
  {
    Inventory& creature_inv = creature->get_inventory();
    if (!creature_inv.merge(item))
    {
      // Add to the end of the inventory
      creature_inv.add(item);
    }
    
    // Display a message if necessary
    if (creature->get_is_player())
    {
      string pick_up_message = TextMessages::get_item_pick_up_message(item);
      
      manager.add_new_message(pick_up_message);
      manager.send();        
    }
    
    return true;
  }
  
  return false;
}

// Base action cost value is 1.
ActionCostValue PickupAction::get_action_cost_value() const
{
  return 1;
}
