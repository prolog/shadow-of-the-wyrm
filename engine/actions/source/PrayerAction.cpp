#include "ClassManager.hpp"
#include "DeityDecisionStrategyFactory.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PrayerAction.hpp"
#include "ReligionManager.hpp"

using std::string;

PrayerAction::PrayerAction()
{
}

// Create the decision strategies surrounding prayer, based on the
// creature's chosen deity.
ActionCostValue PrayerAction::pray(CreaturePtr creature)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map && map->get_map_type() == MAP_TYPE_WORLD)
    {
      IMessageManager& manager = MessageManagerFactory::instance();

      manager.add_new_message(StringTable::get(DeityTextKeys::PRAYER_WORLD_MAP));
      manager.send();

      return 0;
    }

    // Say the prayer.
    say_prayer(creature);
    
    TilePtr creature_tile = MapUtils::get_tile_for_creature(game.get_current_map(), creature);
    
    ReligionManager rm;
    DeityPtr deity = rm.get_active_deity(creature);
    
    // Decide on a course of action.
    IDeityDecisionStrategyPtr deity_decision_strategy = DeityDecisionStrategyFactory::create_deity_decision_strategy(deity->get_id());
    DeityDecisionStrategyHandlerPtr deity_decision_handler = deity_decision_strategy->get_decision(creature);
    
    // Act on that decision.
    DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature, creature_tile);
    
    // Reduce the piety and update the player on the result.
    finish_prayer(creature, decision_implications);

    // Break the Agnostic conduct.
    creature->get_conducts_ref().break_conduct(CONDUCT_TYPE_AGNOSTIC);
  }

  return get_action_cost_value(creature);
}

// If the creature is the player, say a prayer (add a message).
void PrayerAction::say_prayer(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  ReligionManager rm;
  
  if (creature && creature->get_is_player())
  {
    string deity_name_sid = rm.get_deity_name_sid(creature->get_religion().get_active_deity_id());
    string prayer_message = DeityTextKeys::get_prayer_message(deity_name_sid);
    
    manager.add_new_message(prayer_message);
    manager.send();
  }
}

// Reduce the piety by the given amount, and update the player on the result
void PrayerAction::finish_prayer(CreaturePtr creature, const DeityDecisionImplications& decision_implications)
{
  int piety_loss = decision_implications.get_piety_loss();

  // Get the deity and the creature's status with that deity.
  ReligionManager rm;
  ClassManager cm;
  
  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  DeityPtr creature_deity = rm.get_deity(deity_id);
  DeityStatus status = religion.get_deity_status(deity_id);

  ClassPtr cur_class = cm.get_class(creature->get_class_id());
  float piety_cost_multiplier = cur_class->get_piety_cost_multiplier();
  int piety_cost = static_cast<int>(piety_loss * piety_cost_multiplier);
  
  status.decrement_piety(piety_cost);
  religion.set_deity_status(deity_id, status);
  
  if (creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    
    string prayer_message = StringTable::get(decision_implications.get_message_sid());
      
    manager.add_new_message(prayer_message);
    manager.send();
  }
}

ActionCostValue PrayerAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
