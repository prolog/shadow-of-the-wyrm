#include "DecisionStrategyTypes.hpp"

using std::string;

DecisionStrategyID::DecisionStrategyID()
{
}

DecisionStrategyID::~DecisionStrategyID()
{
}

// The decision strategy IDs, used by the configuration file to specify
// a particular class...
//
// ...since C++ doesn't have proper reflection.
//
// Feh.
string DecisionStrategyID::DECISION_STRATEGY_DEFAULT  = "";
string DecisionStrategyID::DECISION_STRATEGY_IMMOBILE = "immobile";
 
