#include "DeityDecisionConstants.hpp"
#include "DeityDecisionStrategy.hpp"
#include "AltarDropDeityDecisionStrategyHandler.hpp"
#include "CompanionDeityDecisionStrategyHandler.hpp"
#include "CrowningDeityDecisionStrategyHandler.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"
#include "FullAPDeityDecisionStrategyHandler.hpp"
#include "FullHPDeityDecisionStrategyHandler.hpp"
#include "HaltBreedingDeityDecisionStrategyHandler.hpp"
#include "ReligionConstants.hpp"
#include "ReligionManager.hpp"
#include "ProtectionDeityDecisionStrategyHandler.hpp"
#include "RestoreStatusDeityDecisionStrategyHandler.hpp"
#include "SacrificeDeityDecisionStrategyHandler.hpp"
#include "SatiateDeityDecisionStrategyHandler.hpp"
#include "SmiteDeityDecisionStrategyHandler.hpp"
#include "UncurseDeityDecisionStrategyHandler.hpp"

using namespace std;

DeityDecisionStrategy::DeityDecisionStrategy(const string& new_deity_id)
: deity_id(new_deity_id)
{
  initialize_decisions();
}

void DeityDecisionStrategy::initialize_decisions()
{
  decisions.clear();

  DeityDecisionStrategyHandlerPtr cur_decision = std::make_unique<DislikeDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));
  
  cur_decision = std::make_unique<CrowningDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<RestoreStatusDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<FullHPDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<HaltBreedingDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));
   
  cur_decision = std::make_unique<SmiteDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<ProtectionDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<FullAPDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<UncurseDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<CompanionDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));

  cur_decision = std::make_unique<SatiateDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(std::move(cur_decision));
}

// Loop through the set of possible decisions.
// The first one that meets the necessary criteria is selected.
// If none meet their criteria, the deity does nothing.
DeityDecisionStrategyHandlerPtr DeityDecisionStrategy::get_decision(CreaturePtr creature)
{
  // The default decision if nothing else is selected.
  DeityDecisionStrategyHandlerPtr decision_strategy = std::make_unique<DoNothingDeityDecisionStrategyHandler>(deity_id);

  for (auto& decision : decisions)
  {
    if (decision->decide(creature))
    {
      decision_strategy = decision->clone();
      break;
    }
  }

  return decision_strategy;
}

DeityDecisionStrategyHandlerPtr DeityDecisionStrategy::get_decision_for_sacrifice(CreaturePtr creature, ItemPtr item)
{
  DeityDecisionStrategyHandlerPtr sacrifice = std::make_unique<SacrificeDeityDecisionStrategyHandler>(deity_id, creature, item);

  return sacrifice;
}

DeityDecisionStrategyHandlerPtr DeityDecisionStrategy::get_decision_for_altar_drop(CreaturePtr dropping_creature, FeaturePtr altar, ItemPtr item)
{
  DeityDecisionStrategyHandlerPtr item_drop = std::make_unique<AltarDropDeityDecisionStrategyHandler>(deity_id, dropping_creature, altar, item);

  return item_drop;
}
