#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "ConsumableAction.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "Food.hpp"
#include "FoodAction.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceManager.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

FoodAction::FoodAction()
{
}

// Try to eat something.  Before trying the inventory, check the items
// on the ground first, prompting the player for each.  Next, check the 
// inventory, and warn the player if there is nothing edible (this costs 
// 0).  Otherwise, bring up the inventory, and filter by items of 
// ITEM_TYPE_FOOD and ITEM_TYPE_PLANT.
//
// If the user selects nothing in this case, the action cost should still
// be 0; otherwise, it should count as a spent action.
ActionCostValue FoodAction::eat(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;

  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);

    list<IItemFilterPtr> display_list = ItemFilterFactory::create_edible_filter();

    action_cost_value = eat_food_off_ground(creature, display_list);

    if (action_cost_value == 0)
    {
      ItemPtr selected_edible_item = am->inventory(creature, creature->get_inventory(), display_list, {}, false);

      if (selected_edible_item)
      {
        if (eat_food(creature, tile, selected_edible_item, creature->get_inventory()))
        {
          // The item has been eaten.  Advance the turn:
          action_cost_value = get_action_cost_value(creature);
        }
      }
    }
  }

  return action_cost_value;
}

ActionCostValue FoodAction::eat_food_off_ground(CreaturePtr creature, const list<IItemFilterPtr>& display_list)
{
  ActionCostValue action_cost_value = 0;
  MapPtr current_map = Game::instance().get_current_map();
  TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);

  if (tile)
  {
    const list<ItemPtr> ground_items = tile->get_items()->get_items_cref();
    list<ItemPtr> edible_ground;
    back_insert_iterator<list<ItemPtr>> back_it(edible_ground);

    copy_if(ground_items.begin(), ground_items.end(), back_it,
      [display_list](ItemPtr item)
    {
      bool is_food = true;

      for (IItemFilterPtr i : display_list)
      {
        is_food = is_food && i->passes_filter(item);
      }

      return is_food;
    });

    // For each item on the ground, check with the creature to see if they 
    // want to eat it.
    for (ItemPtr food : edible_ground)
    {
      ItemIdentifier iid;

      string consumable_desc = iid.get_appropriate_usage_description(food);
      IMessageManager& manager = MM::instance();
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::get_eat_confirmation_message(consumable_desc)));
      bool confirm = creature->get_decision_strategy()->get_confirmation();

      if (confirm)
      {
        eat_food(creature, tile, food, tile->get_items());
        action_cost_value = get_action_cost_value(creature);
        break;
      }
    }
  }

  return action_cost_value;
}

// Eat the selected item.  Return true if it can be eaten, false otherwise.
bool FoodAction::eat_food(CreaturePtr creature, TilePtr tile, ItemPtr food, IInventoryPtr inventory_for_food)
{
  bool turn_advanced = false;

  ConsumablePtr item_as_consumable = std::dynamic_pointer_cast<Consumable>(food);

  if (food)
  {
    ConsumableAction cm;

    // Is the character full?  If not, eat the food.
    HungerClock& hunger = creature->get_hunger_clock_ref();

    if (!hunger.is_stuffed())
    {
      // First add the message about eating the food, because eating can in
      // turn generate other messages (if the food is poisoned, or the creature
      // gets resists, etc).
      add_food_message(creature, food, true);

      // Reduce the quantity of food by 1; if this brings the quantity down to 0
      // (or lower, I guess!) then remove the food from the creature's inventory.
      food->set_quantity(food->get_quantity() - 1);

      if (inventory_for_food)
      {
        if (food->get_quantity() <= 0) inventory_for_food->remove(food->get_id());
      }

      // Many deities don't appreciate cannibalism!
      string corpse_race_id = food->get_additional_property(ConsumableConstants::CORPSE_RACE_ID);
      if (!corpse_race_id.empty() && (corpse_race_id == creature->get_race_id()))
      {
        Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_CANNIBALISM);
      }

      // Likewise, eating undead is decidedly not kosher for many.
      if (!corpse_race_id.empty())
      {
        RaceManager rm;
        RacePtr corpse_race = rm.get_race(corpse_race_id);

        if (corpse_race != nullptr)
        {
          if (corpse_race->get_undead().get_current())
          {
            DeityActionManager& dam = Game::instance().get_deity_action_manager_ref();
            
            dam.notify_action(creature, CreatureActionKeys::ACTION_DESECRATE_GOOD);
            dam.notify_action(creature, CreatureActionKeys::ACTION_DESECRATE_NEUTRAL);
          }
        }
      }

      // Some foods have seeds.
      string seed_item_id = food->get_additional_property(ItemProperties::ITEM_PROPERTIES_SEED_ITEM_ID);
      if (!seed_item_id.empty())
      {
        create_seed_on_tile(creature, tile, seed_item_id);
      }

      cm.consume(creature, item_as_consumable, true /* apply any effects on the food */);
    }
    else
    {
      // Indicate that the creature wasn't able to stuff down the food.
      add_food_message(creature, food, false);
    }

    turn_advanced = true;
  }

  return turn_advanced;
}

// Add a message about whether the creature could eat the item, or not.
void FoodAction::add_food_message(CreaturePtr creature, ItemPtr food, const bool eat_success)
{
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  ItemIdentifier iid;

  string message;

  // Get the appropriate usage description - this will correctly handle if the
  // food is "regular food" (just use the description SID), or a corpse
  // (generate the corpse name based on the creature it represents).
  string item_desc = iid.get_appropriate_usage_description(food);

  if (eat_success)
  {
    message = ActionTextKeys::get_eat_message(creature->get_description_sid(), item_desc, creature->get_is_player());
  }
  else
  {
    message = ActionTextKeys::get_full_message(creature->get_description_sid(), item_desc, creature->get_is_player());
  }

  manager.add_new_message(message);
  manager.send();
}

void FoodAction::create_seed_on_tile(CreaturePtr creature, TilePtr tile, const string& seed_item_id)
{
  if (creature != nullptr && tile != nullptr)
  {
    // Create the seed on the tile.
    ItemPtr seed = ItemManager::create_item(seed_item_id);

    if (seed != nullptr)
    {
      tile->get_items()->add_front(seed);

      if (creature->get_is_player())
      {
        ItemIdentifier iid;
        string usage_desc = iid.get_appropriate_usage_description(seed);

        IMessageManager& manager = MM::instance();
        manager.add_new_message(ActionTextKeys::get_spit_out_message(usage_desc));
        manager.send();
      }
    }
  }
}

ActionCostValue FoodAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
