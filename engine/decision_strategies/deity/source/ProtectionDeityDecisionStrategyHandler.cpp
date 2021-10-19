#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "ProtectionDeityDecisionStrategyHandler.hpp"

using namespace std;

ProtectionDeityDecisionStrategyHandler::ProtectionDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> ProtectionDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<ProtectionDeityDecisionStrategyHandler>(*this);
  return handler;
}

// There must be a hostile creature in visible range for the protection strategy to fire.
bool ProtectionDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  if (creature)
  {
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
    auto creature_map = fov_map->get_creatures();

    for (auto creature_pair : creature_map)
    {
      CreaturePtr fov_creature = creature_pair.second;

      if (fov_creature && fov_creature->hostile_to(creature->get_id()))
      {
        return true;
      }
    }
  }
  
  return false;
}

DeityDecisionImplications ProtectionDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    if (current_map != nullptr)
    {
      int creature_level = creature->get_level().get_current();
      Resistances protect_resists;

      ModifyStatisticsEffect mse;
      Modifier m;

      // Calculate the evade and soak.
      int soak = static_cast<int>(creature_level * DeityDecisionConstants::PROTECT_SOAK_PER_LEVEL);
      int evade = static_cast<int>(creature_level * DeityDecisionConstants::PROTECT_EVADE_PER_LEVEL);

      // Set the resistances.
      protect_resists.set_all_resistances_to(DeityDecisionConstants::PROTECT_RESISTANCE_MODIFIER);

      m.set_soak_modifier(soak);
      m.set_evade_modifier(evade);
      m.set_resistances(protect_resists);

      mse.set_modifier(m);

      // JCD TODO: Do we need to set deity ID as the source of the modifiers?
      // Will that ever matter?
      pair<Coordinate, TilePtr> creature_loc = current_map->get_location_and_tile(creature->get_id());
      ActionManager& am = game.get_action_manager_ref();
      mse.effect(creature, &am, ItemStatus::ITEM_STATUS_UNCURSED, creature_loc.first, creature_loc.second);
    }
  }

  return get_deity_decision_implications(creature, tile);
}

int ProtectionDeityDecisionStrategyHandler::get_piety_amount() const
{
  return 1000;
}

string ProtectionDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_PROTECTION;
}
