#include "DeityActionManager.hpp"
#include "DeityDecisionImplications.hpp"
#include "DeityDecisionStrategyHandlerFactory.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

// Check to see if the deity likes or dislikes (or simply doesn't care)
// about the action just performed, and update the creature's piety
// accordingly.
void DeityActionManager::notify_action(CreaturePtr creature, const string& action_key)
{
  if (creature)
  {
    Game& game = Game::instance();
    Religion& religion = creature->get_religion_ref();
    DeityMap deities = game.get_deities_ref();
    DeityPtr active_deity = deities[religion.get_active_deity_id()];

    if (active_deity)
    {
      if (active_deity->get_dislike(action_key))
      {
        handle_displeasing_action(creature);
      }
      // else if (active_deity->get_like(action_key)) { ... }
    }
  }
}

// Handle a displeasing action by decreasing piety.
void DeityActionManager::handle_displeasing_action(CreaturePtr creature)
{
  if (creature)
  {
    DeityStatus& status = creature->get_active_deity_status_ref();

    // Reduce the creature's piety.
    int original_piety = status.get_piety();

    // Create a default (for now) dislike decision.
    IDeityDecisionStrategyHandlerPtr deity_decision_handler = DeityDecisionStrategyHandlerFactory::create_dislike_decision_strategy_handler();
    DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature);

    // This may have been updated as a result of the decision.
    int new_piety = status.get_piety();

    // If the creature is the player, and if the piety was reduced
    // below zero, show the deity's anger.
    if ((original_piety >= 0) && (new_piety < 0) && creature->get_is_player())
    {
      add_displeasure_message(creature, deity_decision_handler->get_message_sid());
    }
  }
}

// Add a message about the deity being angry.  This is typically only done when
// piety has dropped from being positive to negative.
void DeityActionManager::add_displeasure_message(CreaturePtr creature, const string& displeasure_message_sid)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);
  string displeasure = StringTable::get(displeasure_message_sid);
  
  manager.add_new_message(displeasure);
  manager.send();
}