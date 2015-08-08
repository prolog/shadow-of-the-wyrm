#include "DeityDecisionConstants.hpp"
#include "DeityDecisionStrategy.hpp"
#include "CrowningDeityDecisionStrategyHandler.hpp"
#include "FullAPDeityDecisionStrategyHandler.hpp"
#include "FullHPDeityDecisionStrategyHandler.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"
#include "ReligionConstants.hpp"
#include "ReligionManager.hpp"
#include "ProtectionDeityDecisionStrategyHandler.hpp"
#include "RestoreStatusDeityDecisionStrategyHandler.hpp"
#include "SacrificeDeityDecisionStrategyHandler.hpp"
#include "SatiateDeityDecisionStrategyHandler.hpp"
#include "SmiteDeityDecisionStrategyHandler.hpp"

using namespace std;

DeityDecisionStrategy::DeityDecisionStrategy(const string& new_deity_id)
: deity_id(new_deity_id)
{
  initialize_decisions();
}

void DeityDecisionStrategy::initialize_decisions()
{
  decisions.clear();

  DeityDecisionStrategyHandlerPtr cur_decision = std::make_shared<CrowningDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<FullHPDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<RestoreStatusDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<SmiteDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<ProtectionDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<SatiateDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<FullAPDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<DislikeDeityDecisionStrategyHandler>(deity_id);
  decisions.push_back(cur_decision);
}

// Loop through the set of possible decisions.
// The first one that meets the necessary criteria is selected.
// If none meet their criteria, the deity does nothing.
DeityDecisionStrategyHandlerPtr DeityDecisionStrategy::get_decision(CreaturePtr creature)
{
  // The default decision if nothing else is selected.
  DeityDecisionStrategyHandlerPtr decision_strategy = std::make_shared<DoNothingDeityDecisionStrategyHandler>(deity_id);

  for (DeityDecisionStrategyHandlerPtr decision : decisions)
  {
    if (decision->decide(creature))
    {
      decision_strategy = decision;
      break;
    }
  }

  return decision_strategy;
}

DeityDecisionStrategyHandlerPtr DeityDecisionStrategy::get_decision_for_sacrifice(CreaturePtr creature, ItemPtr item)
{
  DeityDecisionStrategyHandlerPtr sacrifice = std::make_shared<SacrificeDeityDecisionStrategyHandler>(deity_id, item);

  return sacrifice;
}
