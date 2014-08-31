#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "ConsumableAction.hpp"
#include "Conversion.hpp"
#include "Food.hpp"
#include "FoodAction.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

map<HungerLevel, string> FoodAction::hunger_message_sid_map;

FoodAction::FoodAction()
{
}

// Initialize the map of message SIDs.  Messages are shown when the creature
// (the player, realistically) transitions to a new state.
void FoodAction::initialize_hunger_message_sid_map()
{
  hunger_message_sid_map.clear();

  hunger_message_sid_map = std::map<HungerLevel, std::string>{
                             { HUNGER_LEVEL_STUFFED, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STUFFED },
                             {HUNGER_LEVEL_FULL, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_FULL}, 
                             {HUNGER_LEVEL_NORMAL, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_NORMAL},
                             {HUNGER_LEVEL_HUNGRY, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_HUNGRY},
                             {HUNGER_LEVEL_STARVING, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STARVING},
                             {HUNGER_LEVEL_DYING, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_DYING} };
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
    list<IItemFilterPtr> display_list = ItemFilterFactory::create_edible_filter();

    action_cost_value = eat_food_off_ground(creature, display_list);

    if (action_cost_value == 0)
    {
      ItemPtr selected_edible_item = am->inventory(creature, creature->get_inventory(), display_list, false);

      if (selected_edible_item)
      {
        if (eat_food(creature, selected_edible_item))
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
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::get_eat_confirmation_message(consumable_desc)));
      bool confirm = creature->get_decision_strategy()->get_confirmation();

      if (confirm)
      {
        eat_food(creature, food);
        action_cost_value = get_action_cost_value(creature);
        break;
      }
    }
  }

  return action_cost_value;
}

// Eat the selected item.  Return true if it can be eaten, false otherwise.
bool FoodAction::eat_food(CreaturePtr creature, ItemPtr food)
{
  bool turn_advanced = false;

  ConsumablePtr item_as_consumable = std::dynamic_pointer_cast<Consumable>(food);

  if (food)
  {
    ConsumableAction cm;

    // Is the character full?  If not, eat the food.
    HungerClock& hunger = creature->get_hunger_clock_ref();
    int hunger_before = hunger.get_hunger();

    if (!hunger.is_stuffed())
    {
      // First add the message about eating the food, because eating can in
      // turn generate other messages (if the food is poisoned, or the creature
      // gets resists, etc).
      add_food_message(creature, food, true);

      food->set_quantity(food->get_quantity() - 1);
      if (food->get_quantity() == 0) creature->get_inventory()->remove(food->get_id());

      cm.consume(creature, item_as_consumable);

      int hunger_after = hunger.get_hunger();
      add_hunger_level_message_if_necessary(creature, hunger_before, hunger_after);
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
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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

// Add a message about a change in hunger status, if appropriate.
void FoodAction::add_hunger_level_message_if_necessary(CreaturePtr creature, const int old_hunger, const int new_hunger)
{
  HungerLevel old_level = HungerLevelConverter::to_hunger_level(old_hunger);
  HungerLevel new_level = HungerLevelConverter::to_hunger_level(new_hunger);

  if (old_level != new_level)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    if (hunger_message_sid_map.empty())
    {
      initialize_hunger_message_sid_map();
    }

    string message_sid = hunger_message_sid_map[new_level];

    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
  }
}

ActionCostValue FoodAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
