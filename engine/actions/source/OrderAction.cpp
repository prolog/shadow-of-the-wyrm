#include "OrderAction.hpp"
#include "MessageManagerFactory.hpp"
#include "ActionTextKeys.hpp"
#include "CoordUtils.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CreatureUtils.hpp"
#include "DecisionStrategyProperties.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "OrderCommandFactory.hpp"
#include "OrderCommandProcessor.hpp"
#include "OrderKeyboardCommandMap.hpp"
#include "OrderScreen.hpp"
#include "OrderTextKeys.hpp"
#include "RNG.hpp"

using std::string;
using std::vector;

ActionCostValue OrderAction::order(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature)
  {
    MapPtr map = Game::instance().get_current_map();
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    bool leader_and_followers_exist = creature->get_skills().get_value(SkillType::SKILL_GENERAL_LEADERSHIP) > 0 && CreatureUtils::get_followers(creature, map).size() > 0;

    if (leader_and_followers_exist || check_for_followers(creature, manager))
    {
      acv = order_followers(creature, manager);
    }

    manager.send();
  }

  return acv;
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
    bool can_summon = creature->get_skills().get_value(SkillType::SKILL_GENERAL_LEADERSHIP) > 0;

    CommandFactoryPtr command_factory = std::make_unique<OrderCommandFactory>();

    if (decision_strategy)
    {
      bool followers_exist_in_fov = CreatureUtils::get_followers_in_fov(creature).size() > 0;

      KeyboardCommandMapPtr kb_command_map = std::make_unique<OrderKeyboardCommandMap>(followers_exist_in_fov, can_summon);
      OrderScreen os(game.get_display(), followers_exist_in_fov, can_summon);
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

ActionCostValue OrderAction::order_summon(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_SUMMON));

    MapPtr map = Game::instance().get_current_map();
    CreatureMap creatures = CreatureUtils::get_followers(creature, map);
    Coordinate c_coord = map->get_location(creature->get_id());
    vector<Coordinate> summon_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), c_coord.first, c_coord.second, 2);
    std::reverse(summon_coords.begin(), summon_coords.end());

    for (auto c_pair : creatures)
    {
      if (summon_coords.empty())
      {
        break;
      }

      CreaturePtr follower = c_pair.second;

      if (follower != nullptr)
      {
        while (!summon_coords.empty())
        {
          Coordinate sc = summon_coords.back();
          summon_coords.pop_back();

          TilePtr tile = map->at(sc);

          if (tile != nullptr && tile->get_is_available_for_creature(c_pair.second))
          {
            TilePtr sum_old_tile = MapUtils::get_tile_for_creature(map, follower);
            MapUtils::add_or_update_location(map, follower, sc, sum_old_tile);

            break;
          }
        }
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
