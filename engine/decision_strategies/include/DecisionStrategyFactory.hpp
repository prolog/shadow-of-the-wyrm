#pragma once
#include "ClassIdentifiers.hpp"
#include "DecisionStrategy.hpp"

class DecisionStrategyFactory
{
  public:
    static DecisionStrategyPtr create_decision_strategy(const std::string& decision_strategy_id);
    static DecisionStrategyPtr create_decision_strategy(const ClassIdentifier ci);

  protected:

    static void initialize_type_mappings();

    DecisionStrategyFactory();
    ~DecisionStrategyFactory();

    static std::map<ClassIdentifier, std::string> class_id_type_mappings;
};
