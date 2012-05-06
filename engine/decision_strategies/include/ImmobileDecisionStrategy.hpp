#pragma once
#include "Controller.hpp"
#include "DecisionStrategy.hpp"

class ImmobileDecisionStrategy : public DecisionStrategy
{
  public:
    ImmobileDecisionStrategy(ControllerPtr new_controller);
    
    CommandPtr get_decision(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands);
    bool get_confirmation();

  protected:
    ControllerPtr controller;
};
