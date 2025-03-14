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
#include "Setting.hpp"
#include "TileMovementConfirmation.hpp"

using std::string;
using std::vector;

ActionCostValue OrderAction::order(CreaturePtr creature)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature)
  {
    MapPtr map = Game::instance().get_current_map();
    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    bool leader_and_followers_exist = creature->get_skills().get_value(SkillType::SKILL_GENERAL_LEADERSHIP) > 0 && CreatureUtils::get_followers(creature, map).size() > 0;

    if (leader_and_followers_exist || check_for_followers(creature, manager))
    {
      acv = order_followers(creature);
    }

    manager.send();
  }

  return acv;
}

ActionCostValue OrderAction::order_creature(CreaturePtr leader, CreaturePtr cr_to_order)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (leader != nullptr && cr_to_order != nullptr)
  {
    Game& game = Game::instance();
    DecisionStrategy* decision_strategy = leader->get_decision_strategy();
    bool can_summon = leader->get_skills().get_value(SkillType::SKILL_GENERAL_LEADERSHIP) > 0;

    CommandFactoryPtr command_factory = std::make_unique<OrderCommandFactory>();

    if (decision_strategy)
    {
      const CreatureMap& fov_followers = CreatureUtils::get_followers_in_fov(leader);
      bool followers_exist_in_fov = fov_followers.empty() == false;

      KeyboardCommandMapPtr kb_command_map = std::make_unique<OrderKeyboardCommandMap>(followers_exist_in_fov, can_summon);
      OrderScreen os(game.get_display(), followers_exist_in_fov, can_summon);
      string display_s = os.display();
      int input = display_s.at(0);

      CommandPtr order_command = decision_strategy->get_nonmap_decision(false, leader->get_id(), command_factory.get(), kb_command_map.get(), &input, false);
      acv = OrderCommandProcessor::process(leader, order_command.get(), cr_to_order->get_id());
    }
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

ActionCostValue OrderAction::order_followers(CreaturePtr creature)
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
      const CreatureMap& fov_followers = CreatureUtils::get_followers_in_fov(creature);
      bool always_order_all = game.get_settings_ref().get_setting_as_bool(Setting::ALWAYS_GIVE_ORDERS_TO_ALL_FOLLOWERS_IN_RANGE);
      bool followers_exist_in_fov = fov_followers.empty() == false;
      string follower_ids;

      if (!fov_followers.empty() && always_order_all == false)
      {
        // get_follower_for_command(...);
      }

      KeyboardCommandMapPtr kb_command_map = std::make_unique<OrderKeyboardCommandMap>(followers_exist_in_fov, can_summon);
      OrderScreen os(game.get_display(), followers_exist_in_fov, can_summon);
      string display_s = os.display();
      int input = display_s.at(0);

      CommandPtr order_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), &input, false);
      acv = OrderCommandProcessor::process(creature, order_command.get(), follower_ids);
    }
  }

  return acv;
}

ActionCostValue OrderAction::order_attack(CreaturePtr creature, const string& follower_ids)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_ATTACK));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature, follower_ids);
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

ActionCostValue OrderAction::order_follow(CreaturePtr creature, const string& follower_ids)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_FOLLOW));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature, follower_ids);
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

ActionCostValue OrderAction::order_freeze(CreaturePtr creature, const string& follower_ids)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_FREEZE));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature, follower_ids);
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

ActionCostValue OrderAction::order_at_ease(CreaturePtr creature, const string& follower_ids)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(OrderTextKeys::GIVE_ORDER_AT_EASE));

    CreatureMap creatures = CreatureUtils::get_followers_in_fov(creature, follower_ids);
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

ActionCostValue OrderAction::order_summon(CreaturePtr creature, const string& /* follower_ids */)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    creature->get_skills().mark(SkillType::SKILL_GENERAL_LEADERSHIP);

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
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
        for (size_t i = 0; i < summon_coords.size(); i++)
        {
          Coordinate sc = summon_coords.at(i);
          TilePtr tile = map->at(sc);

          if (tile != nullptr && tile->get_is_available_for_creature(c_pair.second))
          {
            Coordinate sum_old_location = map->get_location(follower->get_id());
            TilePtr sum_old_tile = MapUtils::get_tile_for_creature(map, follower);
            TileMovementConfirmation tmc;

            auto movement_details = tmc.get_confirmation_details(follower, map, sum_old_tile, sum_old_location, tile, sc);

            // If moving to this tile would trigger confirmation (eg, trying
            // to move an aquatic creature out of water), skip it and move
            // to the next creature.
            if (!movement_details.get_require_prompt())
            {
              MapUtils::add_or_update_location(map, follower, sc, sum_old_tile);
              summon_coords.erase(summon_coords.begin() + i);

              break;
            }
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

ActionCostValue OrderAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return ActionCostConstants::DEFAULT;
}
