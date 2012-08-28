#include <ncurses.h>

#include <boost/make_shared.hpp>
#include "ActionManager.hpp"
#include "DropManager.hpp"
#include "Game.hpp"
#include "ItemDisplayFilterFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"
#include "Tile.hpp"

using namespace std;
using boost::make_shared;

// Drop the item on to the square, if possible.
ActionCostValue DropManager::drop(CreaturePtr creature, ActionManager * const am)
{  
  ActionCostValue action_cost_value = 0;
  
  Game* game = Game::instance();
  
  if (game && creature)
  {
    MapPtr map = game->get_current_map();
    
    if (map->get_map_type() == MAP_TYPE_WORLD)
    {
      handle_world_drop(creature);
    }
    else
    {
      list<IItemDisplayFilterPtr> no_filter = ItemDisplayFilterFactory::create_empty_filter();
      ItemPtr item_to_drop = am->inventory(creature, creature->get_inventory(), no_filter, false);
      
      if (!item_to_drop)
      {
        handle_no_item_dropped(creature);
      }
      else // Item selected
      {
        do_drop(creature, map, item_to_drop);
      }      
    }
  }
  
  return action_cost_value;
}

// Handle trying to drop stuff on the world map, which is not a valid case.
void DropManager::handle_world_drop(CreaturePtr creature)
{
  MessageManager* manager = MessageManager::instance();
  
  if (manager && creature && creature->get_is_player())
  {
    string drop_not_allowed = StringTable::get(ActionTextKeys::ACTION_DROP_NOT_ALLOWED);
    
    manager->add_new_message(drop_not_allowed);
    manager->send();
  }  
}

// Show the description of the item being dropped, if applicable
void DropManager::handle_item_dropped_message(CreaturePtr creature, ItemPtr item)
{
  MessageManager* manager = MessageManager::instance();
  
  if (manager && item && creature && creature->get_is_player())
  {
    uint quantity = item->get_quantity();
    
    string drop_message = TextMessages::get_item_drop_message(StringTable::get(item->get_usage_description_sid()), quantity);
    
    manager->add_new_message(drop_message);
    manager->send();
  }
  // If it's not the player, and the player is in range, inform the player
  // what the creature dropped.
  else
  {
    // ...
  }  
}

// Handle the case where the intent was to drop, but then nothing was selected.
void DropManager::handle_no_item_dropped(CreaturePtr creature)
{
  MessageManager* manager = MessageManager::instance();
  
  if (manager && creature && creature->get_is_player())
  {
    string no_item_to_drop = StringTable::get(ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED);
    
    manager->add_new_message(no_item_to_drop);
    manager->send();
  }
}

// Do the actual dropping of items.
ActionCostValue DropManager::do_drop(CreaturePtr creature, MapPtr current_map, ItemPtr item_to_drop)
{
  ActionCostValue action_cost_value = 0;
  TilePtr creatures_tile = MapUtils::get_tile_for_creature(current_map, creature);
  MessageManager* manager = MessageManager::instance();
  
  if (item_to_drop)
  {
    uint quantity = item_to_drop->get_quantity();
    uint selected_quantity = quantity;

    if (quantity > 1)
    {
      if (creature && creature->get_is_player())
      {
        // JCD FIXME: Redraw screen here?
        // JCD FIXME
        Game* game = Game::instance();
        game->update_display(creature, current_map, creature->get_decision_strategy()->get_fov_map());
                  
        string quantity_prompt = StringTable::get(ActionTextKeys::ACTION_DROP_QUANTITY_PROMPT);
        manager->add_new_message(quantity_prompt);
        manager->send();
      }
      
      // Get quantity
      selected_quantity = creature->get_decision_strategy()->get_count(quantity);
    }

    // Drop quantity
    if (!item_to_drop->is_valid_quantity(selected_quantity))
    {
      manager->clear_if_necessary();
      string invalid_drop_quantity = StringTable::get(ActionTextKeys::ACTION_DROP_INVALID_QUANTITY);
      manager->add_new_message(invalid_drop_quantity);
      manager->send();
    }
    else
    {
      ItemPtr new_item = ItemPtr(item_to_drop->deep_copy_with_new_id());
      new_item->set_quantity(selected_quantity);
      
      uint old_item_quantity = item_to_drop->get_quantity() - selected_quantity;
      item_to_drop->set_quantity(old_item_quantity);

      if (creatures_tile)
      {
        // Add the item to the list currently on the tile.
        creatures_tile->get_items().add_front(new_item);

        // Display a message if appropriate.
        // If it's the player, remind the user what he or she dropped.
        handle_item_dropped_message(creature, new_item);
      }
      
      // Remove it from the inventory, if the quantity is now zero.
      if (item_to_drop->get_quantity() == 0)
      {
        creature->get_inventory().remove(item_to_drop->get_id());
      }

      // Advance the turn
      action_cost_value = get_action_cost_value();
    }
  }
  
  return action_cost_value;
}

// Dropping always has a base action cost of 1.
ActionCostValue DropManager::get_action_cost_value() const
{
  return 1;
}
