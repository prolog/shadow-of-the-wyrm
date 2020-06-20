#include "Conversion.hpp"
#include "DecisionStrategyProperties.hpp"
#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "HaltBreedingDeityDecisionStrategyHandler.hpp"

using std::string;

HaltBreedingDeityDecisionStrategyHandler::HaltBreedingDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> HaltBreedingDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<HaltBreedingDeityDecisionStrategyHandler>(*this);
  return handler;
}

bool HaltBreedingDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  if (current_map != nullptr)
  {
    CreatureMap creatures = current_map->get_creatures();

    for (const auto& creature_pair : creatures)
    {
      string breeds_s = creature_pair.second->get_decision_strategy()->get_property(DecisionStrategyProperties::DECISION_STRATEGY_BREEDS);
      if (!breeds_s.empty() && (String::to_bool(breeds_s) == true))
      {
        decision = true;
        break;
      }
    }
  }

  return decision;
}

DeityDecisionImplications HaltBreedingDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();
  
  if (current_map != nullptr)
  {
    CreatureMap& creatures = current_map->get_creatures_ref();

    for (auto& cr_pair : creatures)
    {
      cr_pair.second->get_decision_strategy()->remove_property(DecisionStrategyProperties::DECISION_STRATEGY_BREEDS);
    }
  }

  return get_deity_decision_implications(creature, tile);
}

int HaltBreedingDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 400;
}

string HaltBreedingDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_HALT_BREEDING;
}
