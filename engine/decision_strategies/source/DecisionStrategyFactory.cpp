#include "CursesKeyboardController.hpp"
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyTypes.hpp"
#include "ImmobileDecisionStrategy.hpp"
#include "MobileDecisionStrategy.hpp"
#include "NullKeyboardController.hpp"
#include "PlayerDecisionStrategy.hpp"

using namespace std;

map<ClassIdentifier, string> DecisionStrategyFactory::class_id_type_mappings;

DecisionStrategyFactory::DecisionStrategyFactory()
{
}

DecisionStrategyFactory::~DecisionStrategyFactory()
{
}

DecisionStrategyPtr DecisionStrategyFactory::create_decision_strategy(const ClassIdentifier ci)
{
  string decision_strategy_id = DecisionStrategyID::DECISION_STRATEGY_DEFAULT;

  if (class_id_type_mappings.empty())
  {
    initialize_type_mappings();
  }

  map<ClassIdentifier, string>::iterator d_it = class_id_type_mappings.find(ci);

  if (d_it != class_id_type_mappings.end())
  {
    decision_strategy_id = d_it->second;
  }

  return create_decision_strategy(decision_strategy_id);
}

// Create the decision strategy based on the passed-in decision strategy
// identifier.
DecisionStrategyPtr DecisionStrategyFactory::create_decision_strategy(const string& decision_strategy_id)
{
  DecisionStrategyPtr strategy;
  ControllerPtr controller, curses_controller;
  controller = std::make_shared<NullKeyboardController>();
  curses_controller = std::make_shared<CursesKeyboardController>();
  
  if (decision_strategy_id == DecisionStrategyID::DECISION_STRATEGY_IMMOBILE)
  {
    strategy = std::make_shared<ImmobileDecisionStrategy>(controller);
  }
  else if (decision_strategy_id == DecisionStrategyID::DECISION_STRATEGY_MOBILE)
  {
    strategy = std::make_shared<MobileDecisionStrategy>(controller);
  }
  else if (decision_strategy_id == DecisionStrategyID::DECISION_STRATEGY_PLAYER)
  {
    strategy = std::make_shared<PlayerDecisionStrategy>(curses_controller);
  }
  // ??? == PLAYER?  Could be interesting...
  else // Assume == DecisionStrategyID::DECISION_STRATEGY_DEFAULT
  {
    strategy = std::make_shared<ImmobileDecisionStrategy>(controller);
  }
  
  return strategy;
}

void DecisionStrategyFactory::initialize_type_mappings()
{
  class_id_type_mappings.clear();

  class_id_type_mappings.insert(make_pair(CLASS_ID_MOBILE_DECISION_STRATEGY, DecisionStrategyID::DECISION_STRATEGY_MOBILE));
  class_id_type_mappings.insert(make_pair(CLASS_ID_IMMOBILE_DECISION_STRATEGY, DecisionStrategyID::DECISION_STRATEGY_IMMOBILE));
  class_id_type_mappings.insert(make_pair(CLASS_ID_PLAYER_DECISION_STRATEGY, DecisionStrategyID::DECISION_STRATEGY_PLAYER));
}