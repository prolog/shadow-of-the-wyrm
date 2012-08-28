#include <list>
#include <boost/foreach.hpp>
#include "Game.hpp"
#include "Inventory.hpp"
#include "ItemDisplayFilterFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "PickupManager.hpp"
#include "StringConstants.hpp"

using namespace std;

// Try to pick up.
ActionCostValue PickupManager::pick_up(CreaturePtr creature, ActionManager * const am)
{  
  ActionCostValue action_cost_value = 0;

  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();
  
  if (creature && game)
  {
    MapPtr map = game->get_current_map();
    
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      handle_world_map_pickup(creature);
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
            list<IItemDisplayFilterPtr> no_filter = ItemDisplayFilterFactory::create_empty_filter();
            pick_up_item = am->inventory(creature, inv, no_filter, false);
          }
          
          if (pick_up_item)
          {
            // Remove the item from the ground.
            inv.remove(pick_up_item->get_id());
            
            Inventory& creature_inv = creature->get_inventory();
            if (!creature_inv.merge(pick_up_item))
            {
              // Add to the end of the inventory
              creature_inv.add(pick_up_item);
            }

            // Display a message if necessary
            if (creature->get_is_player())
            {
              string pick_up_message = TextMessages::get_item_pick_up_message(pick_up_item);
              
              manager->add_new_message(pick_up_message);
              manager->send();        
            }
          }
          
          // Advance the turn
          action_cost_value = get_action_cost_value();
        }   
      }      
    }
  }

  return action_cost_value;
}

// Handle the case where we're trying to pick up on the world map, which is an invalid case.
void PickupManager::handle_world_map_pickup(CreaturePtr creature)
{
  MessageManager* manager = MessageManager::instance();
  
  if (creature && creature->get_is_player() && manager)
  {
    string pick_up_not_allowed = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED);
    
    manager->add_new_message(pick_up_not_allowed);
    manager->send();
  }
}

// Handle the case where we're trying to pick up from a tile that contains no items.
void PickupManager::handle_empty_tile_pickup(CreaturePtr creature)
{
  MessageManager* manager = MessageManager::instance();
  
  if (creature && creature->get_is_player() && manager)
  {
    string no_item_on_ground = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND);
    
    manager->add_new_message(no_item_on_ground);
    manager->send();
  }  
}

// Base action cost value is 1.
ActionCostValue PickupManager::get_action_cost_value() const
{
  return 1;
}
