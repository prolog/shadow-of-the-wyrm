#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "EffectFactory.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "EvokeAction.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

// Select a wand to evoke
ActionCostValue EvokeAction::evoke(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_type_filter(ITEM_TYPE_WAND);
    ItemPtr selected_item = am->inventory(creature, creature->get_inventory(), display_filter_list, false);
    
    if (selected_item)
    {
      WandPtr wand = dynamic_pointer_cast<Wand>(selected_item);
      
      if (wand)
      {
        // Redraw the screen, since we will have moved from the evoke screen
        // back to the main map.
        Game& game = Game::instance();
        game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
        game.get_display()->redraw();

        action_cost_value = evoke_wand(creature, am, wand);
      }
    }
  }
  
  return action_cost_value;
}

// A wand was selected.  Evoke it: get the potion's nutrition, and then do the magical effect.
//
// JCD FIXME: This, scrolls, potions, etc., all similar.  Look at
// refactoring this.
ActionCostValue EvokeAction::evoke_wand(CreaturePtr creature, ActionManager * const am, WandPtr wand)
{
  ActionCostValue action_cost_value = 0;

  if (creature && wand)
  {
    EffectPtr wand_effect = EffectFactory::create_effect(wand->get_effect_type());
    
    if (wand_effect)
    {
      ItemIdentifier item_id;
      string wand_base_id = wand->get_base_id();
      bool wand_originally_identified = item_id.get_item_identified(wand_base_id);

      // Get the wand's direction.
      pair<bool, Direction> evoke_result = get_evocation_direction(creature);
      bool evoke_successful = evoke_result.first;

      if (evoke_successful)
      {
        // Add a message about evoking.
        add_evocation_message(creature, wand, item_id);
      
        // Reduce the charges on the wand.
        // ...

        // Process the effect.  This will do any necessary updates to the creature, and will also
        // add a status message based on whether the item was identified.
        bool effect_identified = wand_effect->effect(creature, am, wand->get_status());
      
        // Was the item identified?
        if (effect_identified)
        {        
          // If the item was not identified prior to quaffing, identify it now.
          if (!wand_originally_identified)
          {
            item_id.set_item_identified(wand, wand_base_id, true);
          }
        }

        action_cost_value = get_action_cost_value();
      }
    }
  }

  return action_cost_value;
}

void EvokeAction::add_evocation_message(CreaturePtr creature, WandPtr potion, const ItemIdentifier& item_id)
{
  /*
  EffectPtr effect = EffectFactory::create_effect(wand->get_effect_type());
  string base_id = wand->get_base_id();
  
  // Get "You/monster evoke a wand" message
//  string quaff_message = ActionTextKeys::get_quaff_message(creature->get_description_sid(), item_id.get_appropriate_usage_description_sid(base_id), creature->get_is_player());
  
  // Display an appropriate message
  MessageManager& manager = MessageManager::instance();
  
  manager.add_new_message(quaff_message);
  manager.send();
  */
}

// Get the basic cost of evoking a wand.
ActionCostValue EvokeAction::get_action_cost_value() const
{
  return 1;
}

pair<bool, Direction> EvokeAction::get_evocation_direction(CreaturePtr creature)
{
  pair<bool, Direction> evoke_direction_result(false, DIRECTION_UP);
  Direction direction = DIRECTION_UP;

  MessageManager& manager = MessageManager::instance();

  // Make the creature select a direction.
  CommandFactoryPtr command_factory = boost::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = boost::make_shared<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
    manager.send();
  }

  CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(creature->get_id(), command_factory, kb_command_map, 0);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    boost::shared_ptr<DirectionalCommand> dcommand;
    dcommand = boost::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand)
    {
      evoke_direction_result.first = true;
      evoke_direction_result.second = dcommand->get_direction();
    }
  }

  return evoke_direction_result;
}