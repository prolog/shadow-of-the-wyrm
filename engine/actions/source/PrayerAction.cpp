#include "ClassManager.hpp"
#include "DeityDecisionStrategyFactory.hpp"
#include "DeityDecisionStrategyHandlerFactory.hpp"
#include "DeityTextKeys.hpp"
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
    // Say the prayer.
    say_prayer(creature);
    
    // Decide on a course of action.
    IDeityDecisionStrategyPtr deity_decision_strategy = DeityDecisionStrategyFactory::create_deity_decision_strategy();
    DeityDecisionType ddt = deity_decision_strategy->get_decision(creature);
    
    // Act on that decision.
    IDeityDecisionStrategyHandlerPtr deity_decision_handler = DeityDecisionStrategyHandlerFactory::create_decision_strategy_handler(ddt);
    DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature);
    
    // Reduce the piety and update the player on the result.
    finish_prayer(creature, decision_implications);
  }

  return get_action_cost_value();
}

// If the creature is the player, say a prayer (add a message).
void PrayerAction::say_prayer(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);
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
    IMessageManager& manager = MessageManagerFactory::instance(creature);
    
    string prayer_message = StringTable::get(decision_implications.get_message_sid());
      
    manager.add_new_message(prayer_message);
    manager.send();
  }
}

ActionCostValue PrayerAction::get_action_cost_value() const
{
  return 1;
}
