#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "RemoveStatusEffect.hpp"
#include "RestoreStatusDeityDecisionStrategyHandler.hpp"
#include "StatusTypes.hpp"

using namespace std;

RestoreStatusDeityDecisionStrategyHandler::RestoreStatusDeityDecisionStrategyHandler()
: piety_loss(0)
{
  initialize_watched_statuses();
}

// Set the list of statuses that will be used to determine if the deity will
// restore the player.
void RestoreStatusDeityDecisionStrategyHandler::initialize_watched_statuses()
{
  watched_statuses.clear();

  const int statusSize = 11;
  const string statuses[] = {StatusIdentifiers::STATUS_ID_BLINDED,
                             StatusIdentifiers::STATUS_ID_BLOODIED,
                             StatusIdentifiers::STATUS_ID_DISFIGURED,
                             StatusIdentifiers::STATUS_ID_EXPOSED,
                             StatusIdentifiers::STATUS_ID_MUTE,
                             StatusIdentifiers::STATUS_ID_PARALYSIS,
                             StatusIdentifiers::STATUS_ID_POISON,
                             StatusIdentifiers::STATUS_ID_SLOWNESS,
                             StatusIdentifiers::STATUS_ID_SPELLBOUND,
                             StatusIdentifiers::STATUS_ID_STONE,
                             StatusIdentifiers::STATUS_ID_STUNNED};

  vector<string> array_vec(&statuses[0], &statuses[statusSize]);
  watched_statuses.insert(watched_statuses.end(), array_vec.begin(), array_vec.end());
}

// Restore status if at least one watched status is present.
bool RestoreStatusDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  if (creature)
  {
    for (const string& status : watched_statuses)
    {
      if (creature->has_status(status))
      {
        return true;
      }
    }
  }

  return false;
}

DeityDecisionImplications RestoreStatusDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature)
{
  // Always reset the piety cost.
  piety_loss = 0;

  if (creature)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();

    // The piety loss for the first status.  The piety loss for each subsequent
    // status is half of the previous.
    int current_piety_loss = 200;

    for (const string& status : watched_statuses)
    {
      if (creature->has_status(status))
      {
        // Remove the status using the standard methods to ensure that for more
        // complex statuses, like slowness, things are restored properly.
        RemoveStatusEffect deity_decision(status);
        deity_decision.effect(creature, &am, ITEM_STATUS_UNCURSED);

        piety_loss += current_piety_loss;
        current_piety_loss /= 2;
      }
    }
  }

  return get_deity_decision_implications();
}

// Piety loss is based on the number of statuses that were lifted by
// the prayer.
int RestoreStatusDeityDecisionStrategyHandler::get_piety_loss() const
{
  return piety_loss;
}

string RestoreStatusDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_RESTORE_STATUS;
}

