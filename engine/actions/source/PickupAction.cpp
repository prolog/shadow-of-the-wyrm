#include <list>
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
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
#include "Setting.hpp"
#include "StatisticsCalculators.hpp"
#include "TextMessages.hpp"

using namespace std;

// Try to pick up.
ActionCostValue PickupAction::pick_up(CreaturePtr creature, ActionManager * const am, const PickUpType pick_up, const set<ItemType>& pickup_types)
{  
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();
  
  if (creature)
  {
    MapPtr map = game.get_current_map();
    
    if (map->get_map_type() == MapType::MAP_TYPE_WORLD && pick_up != PickUpType::PICK_UP_TYPES)
    {
      handle_world_map_pickup(creature);
    }
    else
    {
      action_cost_value = handle_pickup(creature, map, am, pick_up, pickup_types);
    }
  }

  return action_cost_value;
}

// NPC - pick up a specific ground item
ActionCostValue PickupAction::pick_up(CreaturePtr creature, const string& ground_item_id)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (creature != nullptr && map != nullptr)
  {
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

    if (tile != nullptr)
    {
      ItemPtr ground_item = tile->get_items()->get_from_id(ground_item_id);

      if (ground_item != nullptr)
      {
        CreaturePtr player = game.get_current_player();
        CurrentCreatureAbilities cca;
        IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, CreatureUtils::is_player_or_in_los(creature));

        string item_msg = TextMessages::get_item_pick_up_and_merge_message(!cca.can_see(player), creature, ground_item);
        creature->get_inventory()->merge_or_add(ground_item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        tile->get_items()->remove(ground_item_id);

        manager.add_new_message(item_msg);
        manager.send();

        acv = ActionCostConstants::DEFAULT;
      }
    }
  }

  return acv;
}

ActionCostValue PickupAction::handle_pickup(CreaturePtr creature, MapPtr map, ActionManager * const am, const PickUpType pick_up, const set<ItemType>& pickup_types)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
  if (creature)
  {
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);
    
    if (tile)
    {
      IInventoryPtr inv = tile->get_items();

      // If there is no item, inform the user.
      if (inv->empty() && pick_up != PickUpType::PICK_UP_TYPES)
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
          action_cost_value = handle_pickup_all(creature, map, tile);
        }
        else if (pick_up == PickUpType::PICK_UP_TYPES)
        {
          action_cost_value = handle_pickup_types(creature, map, am, tile, pickup_types);
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
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && map != nullptr && tile != nullptr)
  {
    IInventoryPtr inv = tile->get_items();
    vector<tuple<ItemPtr, bool, uint, std::string>> items_to_take;

    if (inv != nullptr)
    {
      // If there is one item, pick it up.
      uint num_items = inv->size();

      bool can_pick_up = true;
      uint num_able_to_pickup = 0;
      string pickup_sid;

      if (num_items == 1)
      {
        ItemPtr pick_up_item = inv->at(0);

        tuple<bool, uint, string> pickup_details = CreatureUtils::can_pick_up(creature, pick_up_item);
        can_pick_up = std::get<0>(pickup_details);
        num_able_to_pickup = std::get<1>(pickup_details);

        if (!can_pick_up)
        {
          pickup_sid = std::get<2>(pickup_details);
        }

        items_to_take.push_back({pick_up_item, can_pick_up, num_able_to_pickup, pickup_sid});
      }
      // If there are many items, get one of them.
      else
      {
        list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
        vector<ItemPtr> items = am->inventory_multiple(creature, inv, no_filter, {}, false, true);

        for (ItemPtr i : items)
        {
          tuple<bool, uint, string> pickup_details = CreatureUtils::can_pick_up(creature, i);
          can_pick_up = std::get<0>(pickup_details);
          num_able_to_pickup = std::get<1>(pickup_details);
          pickup_sid = std::get<2>(pickup_details);

          items_to_take.push_back({i, can_pick_up, num_able_to_pickup, pickup_sid});
        }
      }

      for (const auto& item_context : items_to_take)
      {
        ItemPtr ic_item = std::get<0>(item_context);
        bool ic_can_take = std::get<1>(item_context);
        uint ic_quantity = std::get<2>(item_context);
        string ic_pickup_sid = std::get<3>(item_context);

        if (ic_item != nullptr && (!ic_can_take && ic_quantity == 0))
        {
          handle_cannot_pickup(creature, ic_pickup_sid);
        }
        else
        {
          bool prompt_for_stacks = (items_to_take.size() == 1) && Game::instance().get_settings_ref().get_setting_as_bool(Setting::PROMPT_ON_STACK_PICKUP);
          action_cost_value = take_item_and_give_to_creature(ic_item, inv, creature, prompt_for_stacks, ic_quantity);
        }
      }
    }
  }

  return action_cost_value;
}

ActionCostValue PickupAction::handle_pickup_all(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && tile != nullptr && map != nullptr)
  {
    bool picked_up = false;
    int addl_stacks_taken = -1;
    IInventoryPtr inv = tile->get_items();
    list<ItemPtr> items = inv->get_items_ref();

    for (ItemPtr item : items)
    {
      tuple<bool, int, string> pickup_details = CreatureUtils::can_pick_up(creature, item);
      if (get<0>(pickup_details) == false && get<1>(pickup_details) == 0)
      {
        handle_cannot_pickup(creature, get<2>(pickup_details));
        break;
      }
      else
      {
        picked_up = true;
        take_item_and_give_to_creature(item, inv, creature, false, get<1>(pickup_details));

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
      SpeedCalculator sc;
      int creature_speed = sc.calculate_current(creature);
      action_cost_value = (addl_stacks_taken * creature_speed) + get_action_cost_value(creature);
    }
  }

  return action_cost_value;
}

ActionCostValue PickupAction::handle_pickup_types(CreaturePtr creature, MapPtr map, ActionManager * const am, TilePtr tile, const set<ItemType>& pickup_types)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;
  bool picked_up = false;

  if (creature && map && tile)
  {
    IInventoryPtr inv = tile->get_items();
    list<ItemPtr> items = inv->get_items_ref();

    for (ItemPtr item : items)
    {
      if (item != nullptr && pickup_types.find(item->get_type()) != pickup_types.end() && autopickup_passes_exclusions(item))
      {
        // Candidate for autopickup.  Check to see if the creature can handle
        // the weight and the total number of items.
        tuple<bool, uint, string> pickup_details = CreatureUtils::can_pick_up(creature, item);

        if (!get<0>(pickup_details) && get<1>(pickup_details) == 0)
        {
          handle_cannot_pickup(creature, get<2>(pickup_details));
        }
        else
        {
          take_item_and_give_to_creature(item, inv, creature, false, get<1>(pickup_details));
        }
      }
    }

    if (picked_up)
    {
      acv = get_action_cost_value(creature);
    }
  }

  return acv;
}

bool PickupAction::autopickup_passes_exclusions(ItemPtr item)
{
  if (item != nullptr)
  {
    const Settings& settings = Game::instance().get_settings_ref();
    bool ignore_corpses = settings.get_setting_as_bool(Setting::AUTOPICKUP_IGNORE_CORPSES);

    if (item->has_additional_property(ConsumableConstants::CORPSE_RACE_ID) && ignore_corpses)
    {
      return false;
    }

    bool ignore_unpaid = settings.get_setting_as_bool(Setting::AUTOPICKUP_IGNORE_UNPAID);

    if (item->get_unpaid() && ignore_unpaid)
    {
      return false;
    }
      
    bool exclude_autopickup_over_limit = settings.get_setting_as_bool(Setting::AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT);
    uint total_weight_oz = item->get_total_weight().get_weight();
    Weight weight_limit_lbs(String::to_int(settings.get_setting(Setting::AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT_LBS)));
    uint weight_limit_oz = weight_limit_lbs.get_weight();

    if (exclude_autopickup_over_limit && total_weight_oz > weight_limit_oz)
    {
      return false;
    }
  }
 
  return true;
}

ActionCostValue PickupAction::take_item_and_give_to_creature(ItemPtr pick_up_item, IInventoryPtr inv, CreaturePtr creature, const bool prompt_for_amount, const uint max_quantity)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (pick_up_item != nullptr && inv != nullptr && creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, true);

    uint quantity = pick_up_item->get_quantity();
    uint amount_to_take = max_quantity;

    if (quantity > 1 && prompt_for_amount)
    {
      if (creature->get_is_player())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PICK_UP_STACK_SIZE));
        manager.send();
      }

      amount_to_take = std::min<uint>(creature->get_decision_strategy()->get_count(quantity), max_quantity);
    }

    if (amount_to_take == 0)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PICK_UP_ZERO));
      manager.send();
    }
    else if (!pick_up_item->is_valid_quantity(amount_to_take) || amount_to_take > max_quantity)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PICK_UP_INVALID_QUANTITY));
      manager.send();
    }
    else
    {
      // Rework the stack sizes based on the amount selected.
      pick_up_item = recalculate_stack_sizes(inv, pick_up_item, quantity, amount_to_take);

      // Check the creature's Lore skill to see if its status is identified.
      potentially_identify_status(creature, pick_up_item);

      if (!merge_into_equipment(creature, pick_up_item))
      {
        merge_or_add_into_inventory(creature, pick_up_item);
      }

      acv = ActionCostConstants::DEFAULT;
    }
  }

  return acv;
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
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

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
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && !player_blind && creature->get_is_player());

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
      item->set_additional_property(ItemProperties::ITEM_PROPERTIES_LORE_CHECKED, std::to_string(true));
      int lore_val = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_LORE);

      if (RNG::percent_chance(lore_val))
      {
        item->set_status_identified(true);
      }
    }
  }
}

ItemPtr PickupAction::recalculate_stack_sizes(IInventoryPtr inv, ItemPtr pick_up_item, const uint quantity, const uint amount_to_take)
{
  ItemPtr item_to_take = pick_up_item;

  if (pick_up_item != nullptr)
  {
    if (amount_to_take > 0 && amount_to_take < quantity)
    {
      // Reduce the quantity on the ground appropriately.
      ItemPtr new_item = ItemPtr(pick_up_item->clone_with_new_id());

      if (new_item != nullptr)
      {
        new_item->set_quantity(amount_to_take);
        item_to_take = new_item;
      }

      pick_up_item->set_quantity(quantity - amount_to_take);
    }
    else if (amount_to_take == quantity)
    {
      // Remove the item from the ground.
      inv->remove(pick_up_item->get_id());
    }
  }

  return item_to_take;
}

// Base action cost value is 1.
ActionCostValue PickupAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 1;
}
