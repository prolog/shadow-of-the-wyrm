#include "OrderAction.hpp"
#include "MessageManagerFactory.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "OrderCommandFactory.hpp"
#include "OrderCommandProcessor.hpp"
#include "OrderKeyboardCommandMap.hpp"
#include "OrderScreen.hpp"

using std::string;

ActionCostValue OrderAction::order(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    if (check_for_skills(creature, manager) && check_for_followers(creature, manager))
    {
      order_followers(creature, manager);
    }

    manager.send();
  }

  return get_action_cost_value(creature);
}

bool OrderAction::check_for_skills(CreaturePtr creature, IMessageManager& manager)
{
  bool has_skills = false;

  if (creature != nullptr)
  {
    CurrentCreatureAbilities cca;

    if (cca.can_give_orders(creature, false))
    {
      has_skills = true;
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ORDER_NO_SKILLS));
    }
  }

  return has_skills;
}

bool OrderAction::check_for_followers(CreaturePtr creature, IMessageManager& manager)
{
  bool has_followers_in_fov = false;

  if (creature != nullptr)
  {
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();

    if (fov_map != nullptr)
    {
      const CreatureMap& creatures = fov_map->get_creatures_ref();
      int num_followers = std::count_if(creatures.begin(), creatures.end(), [creature](std::pair<string, CreaturePtr> p) {return (p.second->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID) == creature->get_id()); });

      if (num_followers > 0)
      {
        has_followers_in_fov = true;
      }
      else
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ORDER_NO_FOLLOWERS));
      }
    }
  }

  return has_followers_in_fov;
}

ActionCostValue OrderAction::order_followers(CreaturePtr creature, IMessageManager& manager)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;
 
  if (creature != nullptr)
  {
    Game& game = Game::instance();
    DecisionStrategy* decision_strategy = creature->get_decision_strategy();

    CommandFactoryPtr command_factory = std::make_unique<OrderCommandFactory>();
    KeyboardCommandMapPtr kb_command_map = std::make_unique<OrderKeyboardCommandMap>();

    if (decision_strategy)
    {
      while (acv > -1)
      {
        OrderScreen os(game.get_display());
        string display_s = os.display();
        int input = display_s.at(0);

        CommandPtr order_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), &input, false);
        acv = OrderCommandProcessor::process(creature, order_command.get());
      }
    }

    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_attack(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_follow(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_guard(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_freeze(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::get_action_cost_value(CreaturePtr creature) const
{
  return ActionCostConstants::DEFAULT;
}
