#include "DeityActionManager.hpp"
#include "DeityDecisionImplications.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

// Check to see if the deity likes or dislikes (or simply doesn't care)
// about the action just performed, and update the creature's piety
// accordingly.
void DeityActionManager::notify_action(CreaturePtr creature, const string& action_key, bool active_deity_only)
{
  if (creature)
  {
    Game& game = Game::instance();
    Religion& religion = creature->get_religion_ref();
    DeityMap deities = game.get_deities_ref();

    vector<DeityPtr> deities_to_notify;

    if (active_deity_only)
    {
      DeityPtr active_deity = deities[religion.get_active_deity_id()];
      deities_to_notify.push_back(active_deity);
    }
    else
    {
      for (auto it = deities.begin(); it != deities.end(); it++)
      {
        DeityPtr cur_deity = it->second;
        
        if (cur_deity)
        {
          deities_to_notify.push_back(cur_deity);
        }
      }
    }

    for (DeityPtr cur_deity : deities_to_notify)
    {
      if (cur_deity->get_dislike(action_key))
      {
        handle_displeasing_action(creature, cur_deity);
      }
      // else if (active_deity->get_like(action_key)) { ... }
    }
  }
}

// Handle a displeasing action by decreasing piety.
void DeityActionManager::handle_displeasing_action(CreaturePtr creature, DeityPtr deity)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    TilePtr creature_tile = MapUtils::get_tile_for_creature(current_map, creature);

    DeityRelations& relations = creature->get_religion_ref().get_deity_relations_ref();
    DeityStatus& status = relations[deity->get_id()];

    // Always reduce the creature's piety with the particular deity.
    int original_piety = status.get_piety();

    // Create a default (for now) dislike decision.
    DeityDecisionStrategyHandlerPtr deity_decision_handler = std::make_shared<DislikeDeityDecisionStrategyHandler>(deity);
    DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature, creature_tile);

    // This may have been updated as a result of the decision.
    int new_piety = original_piety - decision_implications.get_piety_loss();
    status.set_piety(new_piety);

    if (creature->get_religion_ref().get_active_deity_id() == deity->get_id())
    {
      // If the creature is the player, and if the piety was reduced
      // below zero, show the deity's anger.
      if ((original_piety >= 0) && (new_piety < 0) && creature->get_is_player())
      {
        add_displeasure_message(creature, deity_decision_handler->get_message_sid());
      }

      // TODO: If the creature follows the deity, something other than anger
      // may occur.
    }
  }
}

// Add a message about the deity being angry.  This is typically only done when
// piety has dropped from being positive to negative.
void DeityActionManager::add_displeasure_message(CreaturePtr creature, const string& displeasure_message_sid)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  string displeasure = StringTable::get(displeasure_message_sid);
  
  manager.add_new_message(displeasure);
  manager.send();
}