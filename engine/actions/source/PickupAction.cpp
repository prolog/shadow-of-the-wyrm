#include <list>
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CreatureSpeedCalculator.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DisplayItemTypeFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "Inventory.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemProperties.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PickupAction.hpp"
#include "RNG.hpp"
#include "TextMessages.hpp"

using namespace std;

// Try to pick up.
ActionCostValue PickupAction::pick_up(CreaturePtr creature, ActionManager * const am, const PickUpType pick_up)
{  
  ActionCostValue action_cost_value = 0;
  Game& game = Game::instance();
  
  if (creature)
  {
    MapPtr map = game.get_current_map();
    
    if (map->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      handle_world_map_pickup(creature);
    }
    else
    {
      action_cost_value = handle_pickup(creature, map, am, pick_up);
    }
  }

  return action_cost_value;
}

ActionCostValue PickupAction::toggle_autopickup(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    DecisionStrategyPtr dec = creature->get_decision_strategy();

    if (dec != nullptr)
    {
      dec->set_autopickup(!dec->get_autopickup());

      bool ap_value = dec->get_autopickup();
      set<ItemType> autopickup_types = dec->get_autopickup_types();
      vector<string> item_type_names;

      for (const ItemType it : autopickup_types)
      {
        DisplayItemTypePtr dit = DisplayItemTypeFactory::create(it);
        
        if (dit != nullptr)
        {
          item_type_names.push_back(dit->get_description());
        }
      }

      // Add a message about autopickup being on or off.
      IMessageManager& manager = MM::instance();
      manager.add_new_message(ActionTextKeys::get_toggle_autopickup_message(ap_value, item_type_names));
      manager.send();
    }
  }

  return 0; // toggling autopickup is a free action
}

ActionCostValue PickupAction::handle_pickup(CreaturePtr creature, MapPtr map, ActionManager * const am, const PickUpType pick_up)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);
    
    if (tile)
    {
      IInventoryPtr inv = tile->get_items();

      // If there is no item, inform the user.
      if (inv->empty())
      {
        handle_empty_tile_pickup(creature);
      }
      else
      {
        if (pick_up == PickUpType::PICK_UP_SINGLE)
        {
          action_cost_value = handle_pickup_single(creature, map, am, tile);
        }
        else if (pick_up == PickUpType::PICK_UP_ALL)
        {
          action_cost_value = handle_pickup_all(creature, map, am, tile);
        }
        else
        {
          Log::instance().error("Tried to pick up, but an unrecognized pick up type was received.");
        }
      }   
    }      
  }
  
  return action_cost_value;
}

ActionCostValue PickupAction::handle_pickup_single(CreaturePtr creature, MapPtr map, ActionManager * const am, TilePtr tile)
{
  ActionCostValue action_cost_value = 0;

  if (creature != nullptr && map != nullptr && tile != nullptr)
  {
    IInventoryPtr inv = tile->get_items();

    if (inv != nullptr)
    {
      // If there is one item, pick it up.
      uint num_items = inv->size();
      bool can_pick_up = true;
      string pickup_sid;

      ItemPtr pick_up_item;

      if (num_items == 1)
      {
        pick_up_item = inv->at(0);

        pair<bool, string> pickup_details = CreatureUtils::can_pick_up(creature, pick_up_item);

        if (pickup_details.first)
        {
          can_pick_up = true;
        }
        else
        {
          can_pick_up = false;
          pickup_sid = pickup_details.second;
        }
      }

      // If there are many items, get one of them.
      else
      {
        list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
        pick_up_item = am->inventory(creature, inv, no_filter, {}, false);

        pair<bool, string> pickup_details = CreatureUtils::can_pick_up(creature, pick_up_item);
        can_pick_up = pickup_details.first;
        pickup_sid = pickup_details.second;
      }

      if (pick_up_item != nullptr && !can_pick_up)
      {
        handle_cannot_pickup(creature, pickup_sid);
      }
      else
      {
        take_item_and_give_to_creature(pick_up_item, inv, creature);

        // Advance the turn
        action_cost_value = get_action_cost_value(creature);
      }
    }
  }

  return action_cost_value;
}

ActionCostValue PickupAction::handle_pickup_all(CreaturePtr creature, MapPtr map, ActionManager * const am, TilePtr tile)
{
  ActionCostValue action_cost_value = 0;

  if (creature != nullptr && tile != nullptr && map != nullptr)
  {
    bool picked_up = false;
    int addl_stacks_taken = -1;
    IInventoryPtr inv = tile->get_items();
    list<ItemPtr> items = inv->get_items_ref();

    for (ItemPtr item : items)
    {
      pair<bool, string> pickup_details = CreatureUtils::can_pick_up(creature, item);
      
      if (pickup_details.first == false)
      {
        handle_cannot_pickup(creature, pickup_details.second);
        break;
      }
      else
      {
        picked_up = true;
        take_item_and_give_to_creature(item, inv, creature);

        addl_stacks_taken++;
      }
    }

    if (picked_up)
    {
      addl_stacks_taken = std::max<int>(0, addl_stacks_taken);

      // The speed of picking up one item/stack is 1, with this value being
      // added to the creature's speed once the command has finish processing.
      // So the speed of picking up a number of stacks is the number of
      // additional stacks times the creature's speed, plus one.  When this
      // value is returned, it will be added to the creature's speed to
      // make the final total, as usual.
      CreatureSpeedCalculator csc;
      int creature_speed = csc.calculate(creature);
      action_cost_value = (addl_stacks_taken * creature_speed) + get_action_cost_value(creature);
    }
  }

  return action_cost_value;
}

void PickupAction::take_item_and_give_to_creature(ItemPtr pick_up_item, IInventoryPtr inv, CreaturePtr creature)
{
  if (pick_up_item != nullptr && inv != nullptr && creature != nullptr)
  {
    // Remove the item from the ground.
    inv->remove(pick_up_item->get_id());

    // Check the creature's Lore skill to see if its status is identified.
    potentially_identify_status(creature, pick_up_item);

    if (!merge_into_equipment(creature, pick_up_item))
    {
      merge_or_add_into_inventory(creature, pick_up_item);
    }
  }
}

// Handle the case where the creature already has the maximum number of items
// it can hold.
void PickupAction::handle_cannot_pickup(CreaturePtr creature, const string& pickup_details_sid)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  if (creature && creature->get_is_player() && !pickup_details_sid.empty())
  {
    string pick_up_not_allowed = StringTable::get(pickup_details_sid);

    manager.add_new_message(pick_up_not_allowed);
    manager.send();
  }
}

// Handle the case where we're trying to pick up on the world map, which is an invalid case.
void PickupAction::handle_world_map_pickup(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  
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
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  
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
  if (creature)
  {
    Equipment& equipment = creature->get_equipment();
    
    if (equipment.merge(item))
    {
      Game& game = Game::instance();
      CreaturePtr player = game.get_current_player();

      // As all creatures can pick up items, check to see if:
      // - player is blind
      // - player or monster is picking up.
      //
      // If the player is blind, only add a message if it is the player
      // picking up an item.  Otherwise, always add a message.
      CurrentCreatureAbilities cca;
      bool player_blind = !cca.can_see(player);
      string item_merged_into_equipment;

      // Only broadcast if it's the player, or the monster's in range.
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_player_among_creatures(creature, player));

      if (!player_blind || (player_blind && creature->get_is_player()))
      {
        item_merged_into_equipment = TextMessages::get_item_pick_up_and_merge_message(player_blind, creature, item);
      }

      if (!item_merged_into_equipment.empty())
      {
        manager.add_new_message(item_merged_into_equipment);
        manager.send();
      }
      
      return true;
    }
  }
  
  return false;
}

// Merge into the inventory, if possible.  If this is not possible,
// add the item to the inventory.
bool PickupAction::merge_or_add_into_inventory(CreaturePtr creature, ItemPtr item)
{
  if (creature)
  {
    IInventoryPtr creature_inv = creature->get_inventory();
    if (!creature_inv->merge(item))
    {
      // Add to the end of the inventory
      creature_inv->add(item);
    }

    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();
    CurrentCreatureAbilities cca;
    bool player_blind = !cca.can_see(player);

    // Only broadcast if it's the player, or the monster's in range.
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_player_among_creatures(creature, player));

    // Display a message if necessary
    string pick_up_message;
    if (!player_blind || (player_blind && creature->get_is_player()))
    {
      pick_up_message = TextMessages::get_item_pick_up_message(player_blind, creature, item);
    }

    if (!pick_up_message.empty())
    {
      manager.add_new_message(pick_up_message);
      manager.send();
    }

    return true;
  }
  
  return false;
}

void PickupAction::potentially_identify_status(CreaturePtr creature, ItemPtr item)
{
  if (creature != nullptr && item != nullptr)
  {
    if (String::to_bool(item->get_additional_property(ItemProperties::ITEM_PROPERTIES_LORE_CHECKED)) == false)
    {
      item->set_additional_property(ItemProperties::ITEM_PROPERTIES_LORE_CHECKED, Bool::to_string(true));
      int lore_val = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_LORE);

      if (RNG::percent_chance(lore_val))
      {
        item->set_status_identified(true);
      }
    }
  }
}

// Base action cost value is 1.
ActionCostValue PickupAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
