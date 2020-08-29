#include "OrderAction.hpp"
#include "MessageManagerFactory.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CreatureUtils.hpp"
#include "DecisionStrategyProperties.hpp"
#include "Game.hpp"
#include "OrderCommandFactory.hpp"
#include "OrderCommandProcessor.hpp"
#include "OrderKeyboardCommandMap.hpp"
#include "OrderScreen.hpp"
#include "OrderTextKeys.hpp"

using std::string;
using std::vector;

ActionCostValue OrderAction::order(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    if (check_for_followers(creature, manager))
    {
      order_followers(creature, manager);
    }

    manager.send();
  }

  return get_action_cost_value(creature);
}

bool OrderAction::check_for_followers(CreaturePtr creature, IMessageManager& manager)
{
  bool has_followers_in_fov = false;
  CreatureMap followers = CreatureUtils::get_followers_in_fov(creature);

  if (!followers.empty())
  {
    has_followers_in_fov = true;
  }
  else
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ORDER_NO_FOLLOWERS));
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
      OrderScreen os(game.get_display());
      string display_s = os.display();
      int input = display_s.at(0);

      CommandPtr order_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), &input, false);
      acv = OrderCommandProcessor::process(creature, order_command.get());
    }
  }

  return acv;
}

ActionCostValue OrderAction::order_attack(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_ATTACK));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature);
    for (auto c_pair : creatures)
    {
      CreaturePtr follower = c_pair.second;

      if (follower != nullptr)
      {
        set_order(follower, DecisionStrategyProperties::DECISION_STRATEGY_ATTACK_CREATURES_THREATENING_ID, creature->get_id());
      }
    }

    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_follow(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_FOLLOW));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature);
    for (auto c_pair : creatures)
    {
      CreaturePtr follower = c_pair.second;

      if (follower != nullptr)
      {
        set_order(follower, DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID, creature->get_id());
      }
    }

    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_freeze(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_FREEZE));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature);
    for (auto c_pair : creatures)
    {
      CreaturePtr follower = c_pair.second;

      if (follower != nullptr)
      {
        set_order(follower, DecisionStrategyProperties::DECISION_STRATEGY_ORDERED_SENTINEL, std::to_string(true));
      }
    }

    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

ActionCostValue OrderAction::order_at_ease(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_AT_EASE));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature);
    for (auto c_pair : creatures)
    {
      CreaturePtr follower = c_pair.second;

      if (follower != nullptr)
      {
        set_order(follower, DecisionStrategyProperties::DECISION_STRATEGY_AT_EASE, std::to_string(true));
      }
    }

    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

// Void all other orders before setting the current one.
void OrderAction::remove_orders(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    DecisionStrategy* dec = creature->get_decision_strategy();

    if (dec != nullptr)
    {
      vector<string> dec_props = { DecisionStrategyProperties::DECISION_STRATEGY_ATTACK_CREATURES_THREATENING_ID,
                                   DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID,
                                   DecisionStrategyProperties::DECISION_STRATEGY_ORDERED_SENTINEL,
                                   DecisionStrategyProperties::DECISION_STRATEGY_AT_EASE };

      for (auto& p : dec_props)
      {
        dec->remove_property(p);
      }
    }
  }
}

void OrderAction::set_order(CreaturePtr creature, const string& order_id, const string& value)
{
  if (creature != nullptr)
  {
    remove_orders(creature);

    DecisionStrategy* dec = creature->get_decision_strategy();

    if (dec != nullptr)
    {
      dec->set_property(order_id, value);
    }
  }
}

ActionCostValue OrderAction::get_action_cost_value(CreaturePtr creature) const
{
  return ActionCostConstants::DEFAULT;
}
