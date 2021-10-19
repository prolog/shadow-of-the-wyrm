#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "RemoveStatusEffect.hpp"
#include "RestoreStatusDeityDecisionStrategyHandler.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"
#include "UncursingEffect.hpp"
#include "Wearable.hpp"

using namespace std;

RestoreStatusDeityDecisionStrategyHandler::RestoreStatusDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id), piety_loss(0)
{
  initialize_watched_statuses();
}

std::unique_ptr<DeityDecisionStrategyHandler> RestoreStatusDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<RestoreStatusDeityDecisionStrategyHandler>(*this);
  return handler;
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

DeityDecisionImplications RestoreStatusDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  // Always reset the piety cost.
  piety_loss = 0;

  if (creature)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();
    MapPtr current_map = game.get_current_map();

    if (current_map != nullptr)
    {
      Coordinate affected_coord = current_map->get_location(creature->get_id());
      TilePtr affected_tile = current_map->at(affected_coord);

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
          deity_decision.effect(creature, &am, ItemStatus::ITEM_STATUS_UNCURSED, affected_coord, affected_tile);

          piety_loss += current_piety_loss;
          current_piety_loss /= 2;
        }
      }

      uncurse_equipment_with_negative_statuses(creature);
    }
  }

  return get_deity_decision_implications(creature, tile);
}

void RestoreStatusDeityDecisionStrategyHandler::uncurse_equipment_with_negative_statuses(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    EquipmentMap em = creature->get_equipment().get_equipment();

    for (auto& em_pair : em)
    {
      if (em_pair.second &&
          em_pair.second->get_status() == ItemStatus::ITEM_STATUS_CURSED)
      {
        Wearable* w = dynamic_cast<Wearable*>(em_pair.second.get());
        Game& game = Game::instance();
        MapPtr map = game.get_current_map();

        if (w != nullptr && map != nullptr)
        {
          Coordinate cr_coord = map->get_location(creature->get_id());
          TilePtr cr_tile = map->at(cr_coord);

          set<string> ail = w->get_status_ailments().get_ailments();

          for (const string& sa : ail)
          {
            StatusEffectPtr status = StatusEffectFactory::create_status_effect(creature, sa, "");

            if (status != nullptr && status->is_negative())
            {
              UncursingEffect uncurse;
              uncurse.effect(creature, &game.get_action_manager_ref(), ItemStatus::ITEM_STATUS_UNCURSED, cr_coord, cr_tile);
            }
          }
        }
      }
    }
  }
}

// Piety loss is based on the number of statuses that were lifted by
// the prayer.
int RestoreStatusDeityDecisionStrategyHandler::get_piety_amount() const
{
  return piety_loss;
}

string RestoreStatusDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_RESTORE_STATUS;
}

