#include "global_prototypes.hpp"
#include "ClassManager.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "DeityActionManager.hpp"
#include "DeityDecisionImplications.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

// Check to see if the deity likes or dislikes (or simply doesn't care)
// about the action just performed, and update the creature's piety
// accordingly.
void DeityActionManager::notify_action(CreaturePtr creature, MapPtr map, const string& action_key, bool active_deity_only)
{
  Game& game = Game::instance();

  if (creature != nullptr && map != nullptr && !game.get_deities_cref().empty())
  {
    bool cannot_pray = String::to_bool(map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY));
   
    // If we're on a map outside the Nine's dominion, don't notify them of
    // the potential transgression.
    if (cannot_pray)
    {
      return;
    }

    Religion& religion = creature->get_religion_ref();
    const DeityMap& deities = game.get_deities_cref();

    vector<Deity*> deities_to_notify;

    if (active_deity_only)
    {
      auto d_it = deities.find(religion.get_active_deity_id());

      if (d_it != deities.end())
      {
        Deity* active_deity = d_it->second.get();
        deities_to_notify.push_back(active_deity);
      }
    }
    else
    {
      for (auto it = deities.begin(); it != deities.end(); it++)
      {
        Deity* cur_deity = it->second.get();
        
        if (cur_deity != nullptr)
        {
          deities_to_notify.push_back(cur_deity);
        }
      }
    }

    for (Deity* cur_deity : deities_to_notify)
    {
      if (cur_deity->get_dislike(action_key))
      {
        handle_displeasing_action(creature, cur_deity, action_key);
      }
      else if (cur_deity->get_like(action_key))
      {
        handle_pleasing_action(creature, cur_deity, action_key);
      }
    }
  }
}

// Handle a displeasing action by decreasing piety.
void DeityActionManager::handle_displeasing_action(CreaturePtr creature, Deity* deity, const string& action)
{
  if (creature != nullptr && deity != nullptr)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    TilePtr creature_tile = MapUtils::get_tile_for_creature(current_map, creature);

    DeityRelations& relations = creature->get_religion_ref().get_deity_relations_ref();
    DeityStatus& status = relations[deity->get_id()];

    // Always reduce the creature's piety with the particular deity.
    int original_piety = status.get_piety();

    ClassManager cm;
    Class* cr_class = cm.get_class(creature->get_class_id());
    map<string, float> ddm = cr_class->get_deity_dislike_multipliers();
    auto d_it = ddm.find(action);
    float multiplier = 1.0f;

    if (d_it != ddm.end())
    {
      float val = d_it->second;

      // Ignore displeasing actions if val == 0
      if (fequal(val, 0.0f))
      {
        multiplier = val;
      }
    }

    if (multiplier > 0)
    {
      // Create a default (for now) dislike decision.
      DeityDecisionStrategyHandlerPtr deity_decision_handler = std::make_unique<DislikeDeityDecisionStrategyHandler>(deity);
      DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature, creature_tile);

      // This may have been updated as a result of the decision.
      int new_piety = original_piety - static_cast<int>(decision_implications.get_piety_loss() * multiplier);
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
}

void DeityActionManager::handle_pleasing_action(CreaturePtr creature, Deity* deity, const string& action_key)
{
  if (creature != nullptr)
  {
    // ...
    CreatureUtils::add_piety_message_if_player(creature);
  }
}

// Add a message about the deity being angry.  This is typically only done when
// piety has dropped from being positive to negative.
void DeityActionManager::add_displeasure_message(CreaturePtr creature, const string& displeasure_message_sid)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  string displeasure = StringTable::get(displeasure_message_sid);
  
  manager.add_new_message(displeasure);
  manager.send();
}